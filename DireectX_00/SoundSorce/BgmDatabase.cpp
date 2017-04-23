#include "BgmDatabase.h"

#include "LoadWave.h"
#include"XAudio2Interface.h"
#include"SoundMgr.h"

CBgmDatabase::CBgmDatabase()
{
	CreateBgmVoice();
	CreateBuffer();
}


CBgmDatabase::~CBgmDatabase()
{
}

void CBgmDatabase::CreateBgmVoice()
{
	// 全BGMのLoad
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_sourceWaveFormat[loop] = new CLoadWave( bgmdata::BGMName[loop] );
	}

	// SouceVoiceの作成
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		//CXAudio2Interface::Instance()->SetXAudio2SouceVoice(&m_BgmVoices[loop],m_sourceWaveFormat[loop]->GetWaveFormat());
		WAVEFORMATEX* waveformat = m_sourceWaveFormat[loop]->GetWaveFormat();
		GetSoundMgr()->SetXAudio2Souce(&m_BgmVoices[loop], waveformat);
	}
}

void CBgmDatabase::CreateBuffer()
{

	for (int loop = 0 ; loop < bgmdata::MAX_BGM ; ++loop)
	{
		bufferSample[loop] = m_sourceWaveFormat[loop]->GetWaveFormat()->nSamplesPerSec * 3;
		// プライマリバッファ

		primaryLeft[loop] = std::vector<float>(bufferSample[loop]);
		primaryRight[loop] = std::vector<float>(bufferSample[loop]);
		primaryMixed[loop] = std::vector<float>(bufferSample[loop] * 2);
	}

	for (int i = 0; i < bgmdata::MAX_BGM ; i++)
	{
		if (nextFirstSample[i] < m_sourceWaveFormat[i]->GetSamples()  )
		{

			std::size_t readSample = m_sourceWaveFormat[i]->ReadNormalized(nextFirstSample[i],bufferSample[i],&(primaryLeft[i][0]),&primaryRight[i][0] );

			if (readSample > 0)
			{
			
				primaryMixed[i].clear();

				for(std::size_t loop = 0 ; loop < readSample;++loop)
				{
					primaryMixed[i].push_back(primaryLeft[i].at(loop));
					primaryMixed[i].push_back(primaryRight[i].at(loop));
				}

				XAUDIO2_BUFFER bufferDesc = {0};

				bufferDesc.Flags = nextFirstSample[i] + readSample >= m_sourceWaveFormat[i]->GetSamples() ? XAUDIO2_END_OF_STREAM : 0;
				bufferDesc.AudioBytes = readSample * m_sourceWaveFormat[i]->GetWaveFormat()->nBlockAlign;
				bufferDesc.pAudioData = reinterpret_cast<BYTE*> (&(primaryMixed[0]));
				m_BgmVoices[i]->SubmitSourceBuffer(&bufferDesc);

				nextFirstSample[i] += readSample;
				++submitTimes[i];

			}


		}

	}


}

void CBgmDatabase::Play(int BgmListNumb)
{
	m_BgmVoices[BgmListNumb]->Start();
}

void CBgmDatabase::BufferUpdate()
{
	XAUDIO2_VOICE_STATE state[bgmdata::MAX_BGM];

	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_BgmVoices[loop]->GetState(&state[loop]);

		secondaryLeft[loop] = std::vector<float>(bufferSample[loop]);
		secondaryRight[loop] = std::vector<float>(bufferSample[loop]);
		secondaryMixed[loop] = std::vector<float>(bufferSample[loop] * 2);



		if (state[loop].BuffersQueued < 2)
		{
			std::vector< float > & bufferLeft  = submitTimes[loop] & 1 ? secondaryLeft[loop] : primaryLeft[loop];
			std::vector< float > & bufferRight = submitTimes[loop] & 1 ? secondaryRight[loop] : primaryRight[loop];
			std::vector< float > & bufferMixed = submitTimes[loop] & 1 ? secondaryMixed[loop] : primaryMixed[loop];

			std::size_t readSamples = m_sourceWaveFormat[loop]->ReadNormalized(nextFirstSample[loop],bufferSample[loop],&(bufferLeft[0]), &(bufferRight[0]));

			if (readSamples > 0)
			{
				bufferMixed.clear();

				for (std::size_t i = 0; i < readSamples; ++i)
				{
					bufferMixed.push_back(bufferLeft[i]);
					bufferMixed.push_back(bufferRight[i]);
				}

				XAUDIO2_BUFFER bufferDesc = {0};

				bufferDesc.Flags = nextFirstSample[loop] + readSamples >= m_sourceWaveFormat[loop]->GetSamples() ? XAUDIO2_END_OF_STREAM : 0;
				bufferDesc.AudioBytes = readSamples * m_sourceWaveFormat[loop]->GetWaveFormat()->nBlockAlign;
				bufferDesc.pAudioData = reinterpret_cast<BYTE*>(&(bufferMixed[0]));
				m_BgmVoices[loop]->SubmitSourceBuffer(&bufferDesc);

				nextFirstSample[loop] += readSamples;

				++submitTimes[loop];
			}

			if (nextFirstSample[loop] >= m_sourceWaveFormat[loop]->GetSamples())
					nextFirstSample[loop] = 0;
		
		}

	}



}