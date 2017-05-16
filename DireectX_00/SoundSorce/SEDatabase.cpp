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
		m_SeData[loop]->SourceWaveFormat = new CLoadWave(sedata::SEName[loop]);
		m_SeData[loop]->Voice = NULL;
	}

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		WAVEFORMATEX* waveformat = m_SeData[loop]->SourceWaveFormat->GetWaveFormat();
		GetXAudio2Mgr()->SetXAudio2SouceVoice(&m_SeData[loop]->Voice,*waveformat);
	}

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeData[loop]->Voice->SubmitSourceBuffer(&m_SeData[loop]->SourceWaveFormat->PreLoadSound());
	}

	Soundfunc = []() {};

}

///////////////////////////////////////////////////////////
//
//	再生
//
void CSEDatabase::Play(int SeListNumb)
{
	m_SeData[SeListNumb]->Voice->Start();
}

///////////////////////////////////////////////////////////
//
//	停止
//
void CSEDatabase::Stop(int SeListNumb)
{
	m_SeData[SeListNumb]->Voice->Stop();
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
		m_SeData[loop]->Voice->DestroyVoice();
	}

	// 
	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		delete m_SeData[loop]->Voice;
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
		m_SeData[loop]->Voice->SetVolume(Volume);
	}
}

///////////////////////////////////////////////////////////
//
//	Seの単体における音量の設定
//
void CSEDatabase::SetSeVolume(int SetListNumb,float Vol)
{
	m_SeData[SetListNumb]->Voice->SetVolume(Vol);
}