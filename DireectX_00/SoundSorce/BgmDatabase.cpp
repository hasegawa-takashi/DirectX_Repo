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
		m_VoiceData[loop].SourceWaveFormat = new CLoadWave(bgmdata::BGMName[loop]);
		m_VoiceData[loop].Voice = NULL;
	}

	// SouceVoice�̍쐬
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		WAVEFORMATEX* waveformat = m_VoiceData[loop].SourceWaveFormat->GetWaveFormat();
		GetXAudio2Mgr()->SetXAudio2SouceVoice(&m_VoiceData[loop].Voice, *waveformat);
	}

	// �o�b�t�@�̐ݒ�
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_VoiceData[loop].Voice->SubmitSourceBuffer(
			&m_VoiceData[loop].SourceWaveFormat->PreparationBuffer() );
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
		
		XAUDIO2_BUFFER buffer = m_VoiceData[loop].SourceWaveFormat->UpdateBuiffer( m_VoiceData[loop].Voice );

		// ���[�v�Đ�
		if(buffer.pAudioData > 0 && m_VoiceData[loop].Loop )
			m_VoiceData[loop].Voice->SubmitSourceBuffer(&buffer);
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
		m_VoiceData[BgmListNumb].Voice->Start();
	}
	else
	{
		m_VoiceData[BgmListNumb].Voice->Start();
	}
}
/////////////////////////////////////////////////////////////////
//
//	BGM�̍Đ�
//
void CBgmDatabase::Play(int BgmListNumb)
{
	m_VoiceData[BgmListNumb].Voice->Start();
}


/////////////////////////////////////////////////////////////////
//
//	BGM�̒�~[BGM��S��~]
//
void CBgmDatabase::Stop()
{
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_VoiceData[loop].Voice->Stop();
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
		m_VoiceData[BgmListNumb].Voice->Stop();
	}

}

/////////////////////////////////////////////////////////////////
//
//	BGM���ʂ̎擾
//
float CBgmDatabase::GetVolume()
{
	return Volume;
}

/////////////////////////////////////////////////////////////////
//
//	BGM���ʂ̐ݒ�
//
void CBgmDatabase::SetMasterVolume(float vol)
{

	if (vol > 1.0f || vol < 0.0f)
		return;

	Volume = vol;

	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_VoiceData[loop].Voice->SetVolume(Volume);
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
		m_VoiceData[loop].Voice->DestroyVoice();
	}

	// 
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		delete m_VoiceData[loop].SourceWaveFormat;
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
	m_VoiceData[BgmListNumb].Voice->GetVolume(&NowVolume);

	if (NowVolume <= 0)
	{
		m_Fade = false;
		m_VoiceData[BgmListNumb].Voice->SetVolume(0.0f);
		m_VoiceData[BgmListNumb].Voice->Stop();
		Soundfunc = nullptr;
	}

	NowVolume -= MasterVoiceData::FadeSpd;
	m_VoiceData[BgmListNumb].Voice->SetVolume(NowVolume);
}

/////////////////////////////////////////////////////////////////
//
//	�t�F�[�h�C��
//
void CBgmDatabase::FadeIn(int BgmListNumb)
{
	float NowVolume = 0.0f;
	m_VoiceData[BgmListNumb].Voice->GetVolume(&NowVolume);

	if (NowVolume >= Volume)
	{
		m_Fade = false;
		m_VoiceData[BgmListNumb].Voice->SetVolume(Volume);
		Soundfunc = nullptr;
	}
	NowVolume += MasterVoiceData::FadeSpd;
	m_VoiceData[BgmListNumb].Voice->SetVolume(NowVolume);
}

void CBgmDatabase::ChangeReverv(int ListNumb, float walltype, float roomsize)
{
	m_VoiceData[ListNumb].VoiceEffect->SetReverbVolume(walltype, roomsize);
}

void CBgmDatabase::OffReverv()
{
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_VoiceData[loop].VoiceEffect->offsetReverbVolume();
	}
}

void CBgmDatabase::ChangeEcho(int ListNumb, float Delay, float feedback, float wetdry)
{
	m_VoiceData[ListNumb].VoiceEffect->SetEchoVolume(Delay, feedback, wetdry);
}

void CBgmDatabase::OffEcho()
{
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_VoiceData[loop].VoiceEffect->offsetEchoVolume();
	}
}

void CBgmDatabase::ChangePitch(int ListNumb, float PitchRate)
{
	m_VoiceData[ListNumb].VoiceEffect->PitchRate(PitchRate);
}