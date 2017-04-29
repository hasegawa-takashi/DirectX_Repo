#include "BgmDatabase.h"

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
		m_BgmVoices[loop]->SubmitSourceBuffer( &m_sourceWaveFormat[loop]->PreparationBuffer() );
	}

	Soundfunc = []() {};
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

	if (Soundfunc != NULL)
	{
		Soundfunc();
	}

}

/////////////////////////////////////////////////////////////////
//
//	BGM�̍Đ�
//
void CBgmDatabase::Play(int BgmListNumb , bool fadein)
{
	if (fadein)
	{
		Soundfunc = std::bind(&CBgmDatabase::FadeIn, this, fadein);
		//Soundfunc = std::bind( &FadeIn, this, BgmListNumb);
	}
	else
	{
		m_BgmVoices[BgmListNumb]->Start();
	}
}
/////////////////////////////////////////////////////////////////
//
//	BGM�̍Đ�
//
void CBgmDatabase::Play(int BgmListNumb)
{
	m_BgmVoices[BgmListNumb]->Start();
}


/////////////////////////////////////////////////////////////////
//
//	BGM�̒�~[BGM��S��~]
//
void CBgmDatabase::Stop()
{
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_BgmVoices[loop]->Stop();
	}
}
/////////////////////////////////////////////////////////////////
//
//	BGM�̒�~[BGM��I���~]
//
void CBgmDatabase::Stop(int BgmListNumb , bool fadeOut)
{
	
	if (fadeOut)
	{
		Soundfunc = std::bind(&CBgmDatabase::FadeIn, this, fadeOut);
	}
	else
	{
		m_BgmVoices[BgmListNumb]->Stop();
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

/////////////////////////////////////////////////////////////////
//
//	�t�F�[�h�A�E�g
//
void CBgmDatabase::FadeOut(int BgmListNumb)
{
	float NowVolume = 0.0f;
	m_BgmVoices[BgmListNumb]->GetVolume(&NowVolume);

	if (NowVolume <= 0)
	{
		m_Fade = false;
		m_BgmVoices[BgmListNumb]->SetVolume(0.0f);
		Soundfunc = []() {};
	}
	NowVolume -= MasterVoiceData::FadeSpd;
	m_BgmVoices[BgmListNumb]->SetVolume(NowVolume);
}

/////////////////////////////////////////////////////////////////
//
//	�t�F�[�h�C��
//
void CBgmDatabase::FadeIn(int BgmListNumb)
{
	float NowVolume = 0.0f;
	m_BgmVoices[BgmListNumb]->GetVolume(&NowVolume);

	if (NowVolume >= Volume)
	{
		m_Fade = false;
		m_BgmVoices[BgmListNumb]->SetVolume(Volume);
		Soundfunc = []() {};
	}
	NowVolume += MasterVoiceData::FadeSpd;
	m_BgmVoices[BgmListNumb]->SetVolume(NowVolume);
}

/////////////////////////////////////////////////////////////////
//
//	�s�b�`���[�g�̕ύX�֐�
//
void CBgmDatabase::PitchRate(int BgmListNumb,float PitchRate)
{
	m_BgmVoices[0]->SetFrequencyRatio(PitchRate);
}