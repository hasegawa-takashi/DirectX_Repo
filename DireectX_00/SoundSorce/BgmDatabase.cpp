#include "BgmDatabase.h"

#include "LoadWave.h"

CBgmDatabase::CBgmDatabase()
{
	CreateBgmVoice();
}


CBgmDatabase::~CBgmDatabase()
{
	Close();
}

/////////////////////////////////////////////////////////////////
//
//	SouceVoice�̍쐬
//
void CBgmDatabase::CreateBgmVoice()
{
	// �SBGM��Load
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_sourceWaveFormat[loop] = new CLoadWave( bgmdata::BGMName[loop] );
		m_BgmVoices[loop] = NULL;
	}

	// SouceVoice�̍쐬
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		WAVEFORMATEX* waveformat = m_sourceWaveFormat[loop]->GetWaveFormat();
		GetXAudio2Mgr()->SetXAudio2SouceVoice(&m_BgmVoices[loop], *waveformat);
	}

	// �o�b�t�@�̐ݒ�
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_BgmVoices[loop]->SubmitSourceBuffer(&m_sourceWaveFormat[loop]->PreparationBuffer());
	}

}

/////////////////////////////////////////////////////////////////
//
//	SouceVoice�̐ݒ�
//
void CBgmDatabase::Update()
{
	// �o�b�t�@�̍X�V
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		XAUDIO2_BUFFER buffer = m_sourceWaveFormat[loop]->UpdateBuiffer(m_BgmVoices[loop]);
		if(buffer.pAudioData > 0)
			m_BgmVoices[loop]->SubmitSourceBuffer(&buffer);
	}
}

/////////////////////////////////////////////////////////////////
//
//	BGM�̍Đ�
//
void CBgmDatabase::Play(int BgmListNumb , bool fadein = false)
{
	HRESULT hr;

	m_BgmVoices[BgmListNumb]->Start();

	if (fadein)
	{
		FadeIn();
	}
}

/////////////////////////////////////////////////////////////////
//
//	BGM�̒�~
//
void CBgmDatabase::Stop(bool fadein = false)
{
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_BgmVoices[loop]->Stop();
	}
}

/////////////////////////////////////////////////////////////////
//
//	BGM���ʂ̎擾
//
float CBgmDatabase::GetBgmVolume()
{
	return Volume;
}

/////////////////////////////////////////////////////////////////
//
//	BGM���ʂ̐ݒ�
//
void CBgmDatabase::SetBgmVolume(float vol)
{
	Volume = vol;

	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_BgmVoices[loop]->SetVolume(Volume);
	}
}

/////////////////////////////////////////////////////////////////
//
//	�I������
//
void CBgmDatabase::Close()
{
	// ���Ǝn��
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_BgmVoices[loop]->DestroyVoice();
	}

	// 
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		delete[] m_sourceWaveFormat;
	}
}

void CBgmDatabase::FadeOut()
{
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		float NowVolume = 0.0f;
		m_BgmVoices[loop]->GetVolume(&NowVolume);

		if (NowVolume <= 0)
		{
			m_Fade = false;
			m_BgmVoices[loop]->SetVolume(0.0f);
		}
		NowVolume -= MasterVoiceData::FadeSpd;
		m_BgmVoices[loop]->SetVolume(NowVolume);
	}
}

void CBgmDatabase::FadeIn()
{
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		float NowVolume = 0.0f;
		m_BgmVoices[loop]->GetVolume(&NowVolume);

		if (NowVolume >= Volume)
		{
			m_Fade = false;
			m_BgmVoices[loop]->SetVolume(Volume);
		}
		NowVolume += MasterVoiceData::FadeSpd;
		m_BgmVoices[loop]->SetVolume(NowVolume);
	}
}