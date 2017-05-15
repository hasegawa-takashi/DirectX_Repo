#include "SEDatabase.h"

///////////////////////////////////////////////////////////
//
//	準備
//
CSEDatabase::CSEDatabase()
{
	CreateSourceVoice();
	
	Volume = 1.0f;

}

///////////////////////////////////////////////////////////
//
//	かたずけ
//
CSEDatabase::~CSEDatabase()
{
	Close();
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
//	再生
//
void CSEDatabase::Play(int SeListNumb)
{
	m_SeVoices[SeListNumb]->Start();
}

///////////////////////////////////////////////////////////
//
//	停止
//
void CSEDatabase::Stop(int SeListNumb)
{
	m_SeVoices[SeListNumb]->Stop();
}

///////////////////////////////////////////////////////////
//
//	更新処理
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
//	かたずけ
//
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
		delete m_sourceWaveFormat[loop];
	}

	//m_Effects->Release();
}

///////////////////////////////////////////////////////////
//
//	現在ボリュームの取得
//
float CSEDatabase::GetSeVolume()
{
	return Volume;
}

///////////////////////////////////////////////////////////
//
//	Seの全体音量の設定
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
//	Seの単体における音量の設定
//
void CSEDatabase::SetSeVolume(int SetListNumb,float Vol)
{
	m_SeVoices[SetListNumb]->SetVolume(Vol);
}