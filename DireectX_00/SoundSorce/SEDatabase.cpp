#include "SEDatabase.h"



CSEDatabase::CSEDatabase()
{
	CreateSourceVoice();
	CreateVoiceEffect();

	Volume = 1.0f;

}


CSEDatabase::~CSEDatabase()
{
	Close();
	m_reverb->Release();
}

///////////////////////////////////////////////////////////
//
//	ソースボイスのせってい
//
void CSEDatabase::CreateSourceVoice()
{
	for (int loop = 0 ; loop < sedata::MAX_SE ; ++loop)
	{
		m_sourceWaveFormat[loop] = new CLoadWave(sedata::SEName[loop]);
		m_SeVoices[loop] = NULL;
	}

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		WAVEFORMATEX* waveformat = m_sourceWaveFormat[loop]->GetWaveFormat();
		GetXAudio2Mgr()->SetXAudio2SouceVoice(&m_SeVoices[loop],*waveformat);
	}

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->SubmitSourceBuffer(&m_sourceWaveFormat[loop]->PreLoadSound());
	}

	Soundfunc = []() {};

}

///////////////////////////////////////////////////////////
//
//	えふぇくとのせってい
//
void CSEDatabase::CreateVoiceEffect()
{
	CreateFX(__uuidof(::FXReverb), &m_reverb);

	m_desc.InitialState = TRUE;
	m_desc.OutputChannels = 2;
	m_desc.pEffect = m_reverb;

	m_chain.pEffectDescriptors = &m_desc;
	m_chain.EffectCount = 1;

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->SetEffectChain(&m_chain);
	}

	m_Reverbpram.Diffusion = FXREVERB_DEFAULT_DIFFUSION;
	m_Reverbpram.RoomSize = FXREVERB_DEFAULT_ROOMSIZE;


	// 色々やっているけどリバーブの設定だけしてます。
	//他にも色々あるらしい
	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->SetEffectParameters(0,&m_Reverbpram,sizeof(FXREVERB_PARAMETERS));
	}


}

void CSEDatabase::Play(int SeListNumb)
{
	m_SeVoices[SeListNumb]->Start();
}

void CSEDatabase::Stop(int SeListNumb)
{
	m_SeVoices[SeListNumb]->Stop();
}

void CSEDatabase::Update()
{
	if (Soundfunc != NULL)
	{
		Soundfunc();
	}
}

void CSEDatabase::Close()
{
	// あと始末
	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->DestroyVoice();
	}

	// 
	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		delete[] m_sourceWaveFormat[loop];
	}
}

float CSEDatabase::GetSeVolume()
{
	return Volume;
}

void CSEDatabase::SetSeVolume(float Vol)
{
	Volume = Vol;

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->SetVolume(Volume);
	}
}

void CSEDatabase::PitchRate(int BgmListNumb, float PitchRate)
{
	m_SeVoices[BgmListNumb]->SetFrequencyRatio(PitchRate);
}