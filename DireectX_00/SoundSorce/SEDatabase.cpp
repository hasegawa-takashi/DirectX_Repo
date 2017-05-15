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
//	�Đ�
//
void CSEDatabase::Play(int SeListNumb)
{
	m_SeVoices[SeListNumb]->Start();
}

///////////////////////////////////////////////////////////
//
//	��~
//
void CSEDatabase::Stop(int SeListNumb)
{
	m_SeVoices[SeListNumb]->Stop();
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
		m_SeVoices[loop]->DestroyVoice();
	}

	// 
	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		delete m_sourceWaveFormat[loop];
	}

	//m_Effects->Release();
}

///////////////////////////////////////////////////////////
//
//	���݃{�����[���̎擾
//
float CSEDatabase::GetSeVolume()
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
		m_SeVoices[loop]->SetVolume(Volume);
	}
}

///////////////////////////////////////////////////////////
//
//	Se�̒P�̂ɂ����鉹�ʂ̐ݒ�
//
void CSEDatabase::SetSeVolume(int SetListNumb,float Vol)
{
	m_SeVoices[SetListNumb]->SetVolume(Vol);
}