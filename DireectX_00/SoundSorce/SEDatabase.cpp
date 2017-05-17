#include "SEDatabase.h"

///////////////////////////////////////////////////////////
//
//	����
//
CSEDatabase::CSEDatabase()
{
	CreateSourceVoice();
	
	Volume = 1.0f;

}

///////////////////////////////////////////////////////////
//
//	��������
//
CSEDatabase::~CSEDatabase()
{
	Close();
}

///////////////////////////////////////////////////////////
//
//	�\�[�X�{�C�X�̂����Ă�
//
void CSEDatabase::CreateSourceVoice()
{
	for (int loop = 0 ; loop < sedata::MAX_SE ; ++loop)
	{
		m_VoiceData[loop]->SourceWaveFormat = new CLoadWave(sedata::SEName[loop]);
		m_VoiceData[loop]->Voice = NULL;
	}

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		WAVEFORMATEX* waveformat = m_VoiceData[loop]->SourceWaveFormat->GetWaveFormat();
		GetXAudio2Mgr()->SetXAudio2SouceVoice(&m_VoiceData[loop]->Voice,*waveformat);
	}

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_VoiceData[loop]->Voice->SubmitSourceBuffer(&m_VoiceData[loop]->SourceWaveFormat->PreLoadSound());
		m_VoiceData[loop]->VoiceEffect = new CVoiceEffect(m_VoiceData[loop]->Voice);
	}

	Soundfunc = []() {};

}

///////////////////////////////////////////////////////////
//
//	�Đ�
//
void CSEDatabase::Play(int SeListNumb)
{
	m_VoiceData[SeListNumb]->Voice->Start();
}

///////////////////////////////////////////////////////////
//
//	�Đ�
//
void CSEDatabase::Play(int SeListNumb, bool fadein)
{
	m_VoiceData[SeListNumb]->Voice->Start(fadein);
}

///////////////////////////////////////////////////////////
//
//	��~
//
void CSEDatabase::Stop(int SeListNumb,bool fadeout)
{
	m_VoiceData[SeListNumb]->Voice->Stop();
}

///////////////////////////////////////////////////////////
//
//	�X�V����
//
void CSEDatabase::Update()
{
	if (Soundfunc != NULL)
	{
		Soundfunc();
	}
}

///////////////////////////////////////////////////////////
//
//	��������
//
void CSEDatabase::Close()
{
	// ���Ǝn��
	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_VoiceData[loop]->Voice->DestroyVoice();
	}

	// 
	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		delete m_VoiceData[loop]->Voice;
	}

	//m_Effects->Release();
}

///////////////////////////////////////////////////////////
//
//	���݃{�����[���̎擾
//
float CSEDatabase::GetVolume()
{
	return Volume;
}

///////////////////////////////////////////////////////////
//
//	Se�̑S�̉��ʂ̐ݒ�
//
void CSEDatabase::SetMasterVolume(float Vol)
{
	Volume = Vol;

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_VoiceData[loop]->Voice->SetVolume(Volume);
	}
}

///////////////////////////////////////////////////////////
//
//	Se�̒P�̂ɂ����鉹�ʂ̐ݒ�
//
void CSEDatabase::SetSeVolume(int SetListNumb,float Vol)
{
	m_VoiceData[SetListNumb]->Voice->SetVolume(Vol);
}

void CSEDatabase::ChangeReverv(int ListNumb, float walltype, float roomsize)
{
	m_VoiceData[ListNumb]->VoiceEffect->SetReverbVolume(walltype,roomsize);
}

void CSEDatabase::OffReverv()
{
	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_VoiceData[loop]->VoiceEffect->offsetReverbVolume();
	}
}

void CSEDatabase::ChangeEcho(int ListNumb, float Delay, float feedback, float wetdry)
{
	m_VoiceData[ListNumb]->VoiceEffect->SetEchoVolume(Delay,feedback, wetdry);
}

void CSEDatabase::OffEcho()
{
	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_VoiceData[loop]->VoiceEffect->offsetEchoVolume();
	}
}

void CSEDatabase::ChangePitch(int ListNumb, float PitchRate)
{
	m_VoiceData[ListNumb]->VoiceEffect->PitchRate(PitchRate);
}

void CSEDatabase::FadeOut(int BgmListNumb)
{
	float NowVolume = 0.0f;
	m_VoiceData[BgmListNumb]->Voice->GetVolume(&NowVolume);

	if (NowVolume <= 0)
	{
		m_VoiceData[BgmListNumb]->Fade = false;
		m_VoiceData[BgmListNumb]->Voice->SetVolume(0.0f);
		m_VoiceData[BgmListNumb]->Voice->Stop();
		Soundfunc = nullptr;
	}

	NowVolume -= MasterVoiceData::FadeSpd;
	m_VoiceData[BgmListNumb]->Voice->SetVolume(NowVolume);
}

void CSEDatabase::FadeIn(int BgmListNumb)
{
	float NowVolume = 0.0f;
	m_VoiceData[BgmListNumb]->Voice->GetVolume(&NowVolume);

	if (NowVolume >= Volume)
	{
		m_VoiceData[BgmListNumb]->Fade = false;
		m_VoiceData[BgmListNumb]->Voice->SetVolume(Volume);
		Soundfunc = nullptr;
	}
	NowVolume += MasterVoiceData::FadeSpd;
	m_VoiceData[BgmListNumb]->Voice->SetVolume(NowVolume);
}