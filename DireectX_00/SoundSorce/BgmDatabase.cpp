#include "BgmDatabase.h"

CBgmDatabase::CBgmDatabase()
{
	CreateSourceVoice();

	Volume = 1.0f;
}

CBgmDatabase::~CBgmDatabase()
{
	Close();
}

/////////////////////////////////////////////////////////////////
//
//	SouceVoice�̍쐬
//
void CBgmDatabase::CreateSourceVoice()
{
	// �SBGM��Load
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_BgmData[loop]->SourceWaveFormat = new CLoadWave(bgmdata::BGMName[loop]);
		m_BgmData[loop]->Voice = NULL;
	}

	// SouceVoice�̍쐬
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		WAVEFORMATEX* waveformat = m_BgmData[loop]->SourceWaveFormat->GetWaveFormat();
		GetXAudio2Mgr()->SetXAudio2SouceVoice(&m_BgmData[loop]->Voice, *waveformat);
	}

	// �o�b�t�@�̐ݒ�
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_BgmData[loop]->Voice->SubmitSourceBuffer(
			&m_BgmData[loop]->SourceWaveFormat->PreparationBuffer() );
	}

	Soundfunc = nullptr;
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
		//XAUDIO2_BUFFER buffer = m_sourceWaveFormat[loop]->UpdateBuiffer(m_BgmVoices[loop]);
		
		XAUDIO2_BUFFER buffer = m_BgmData[loop]->SourceWaveFormat->UpdateBuiffer( m_BgmData[loop]->Voice );

		// ���[�v�Đ�
		if(buffer.pAudioData > 0 && m_BgmData[loop]->Loop )
			m_BgmData[loop]->Voice->SubmitSourceBuffer(&buffer);
	}

	if (Soundfunc != nullptr)
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
		Soundfunc = std::bind(&CBgmDatabase::FadeIn, this, BgmListNumb);
		m_BgmData[BgmListNumb]->Voice->Start();
	}
	else
	{
		m_BgmData[BgmListNumb]->Voice->Start();
	}
}
/////////////////////////////////////////////////////////////////
//
//	BGM�̍Đ�
//
void CBgmDatabase::Play(int BgmListNumb)
{
	m_BgmData[BgmListNumb]->Voice->Start();
}


/////////////////////////////////////////////////////////////////
//
//	BGM�̒�~[BGM��S��~]
//
void CBgmDatabase::Stop()
{
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_BgmData[loop]->Voice->Stop();
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
		Soundfunc = std::bind(&CBgmDatabase::FadeOut, this, BgmListNumb);
	}
	else
	{
		m_BgmData[BgmListNumb]->Voice->Stop();
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

	if (vol > 1.0f || vol < 0.0f)
		return;

	Volume = vol;

	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_BgmData[loop]->Voice->SetVolume(Volume);
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
		m_BgmData[loop]->Voice->DestroyVoice();
	}

	// 
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		delete m_BgmData[loop]->SourceWaveFormat;
	}

	Soundfunc = nullptr;

}

/////////////////////////////////////////////////////////////////
//
//	�t�F�[�h�A�E�g
//
void CBgmDatabase::FadeOut(int BgmListNumb)
{
	float NowVolume = 0.0f;
	m_BgmData[BgmListNumb]->Voice->GetVolume(&NowVolume);

	if (NowVolume <= 0)
	{
		m_Fade = false;
		m_BgmData[BgmListNumb]->Voice->SetVolume(0.0f);
		m_BgmData[BgmListNumb]->Voice->Stop();
		Soundfunc = nullptr;
	}

	NowVolume -= MasterVoiceData::FadeSpd;
	m_BgmData[BgmListNumb]->Voice->SetVolume(NowVolume);
}

/////////////////////////////////////////////////////////////////
//
//	�t�F�[�h�C��
//
void CBgmDatabase::FadeIn(int BgmListNumb)
{
	float NowVolume = 0.0f;
	m_BgmData[BgmListNumb]->Voice->GetVolume(&NowVolume);

	if (NowVolume >= Volume)
	{
		m_Fade = false;
		m_BgmData[BgmListNumb]->Voice->SetVolume(Volume);
		Soundfunc = nullptr;
	}
	NowVolume += MasterVoiceData::FadeSpd;
	m_BgmData[BgmListNumb]->Voice->SetVolume(NowVolume);
}
