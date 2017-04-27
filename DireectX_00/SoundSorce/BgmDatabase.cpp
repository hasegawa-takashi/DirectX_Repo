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
//	SouceVoiceの作成
//
void CBgmDatabase::CreateBgmVoice()
{
	// 全BGMのLoad
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_sourceWaveFormat[loop] = new CLoadWave( bgmdata::BGMName[loop] );
		m_BgmVoices[loop] = NULL;
	}

	// SouceVoiceの作成
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		WAVEFORMATEX* waveformat = m_sourceWaveFormat[loop]->GetWaveFormat();
		GetXAudio2Mgr()->SetXAudio2SouceVoice(&m_BgmVoices[loop], *waveformat);
	}

	// バッファの設定
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_BgmVoices[loop]->SubmitSourceBuffer(&m_sourceWaveFormat[loop]->PreparationBuffer());
	}

}

/////////////////////////////////////////////////////////////////
//
//	SouceVoiceの設定
//
void CBgmDatabase::Update()
{
	// バッファの更新
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		XAUDIO2_BUFFER buffer = m_sourceWaveFormat[loop]->UpdateBuiffer(m_BgmVoices[loop]);
		if(buffer.pAudioData > 0)
			m_BgmVoices[loop]->SubmitSourceBuffer(&buffer);
	}
}

/////////////////////////////////////////////////////////////////
//
//	BGMの再生
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
//	BGMの停止
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
//	BGM音量の取得
//
float CBgmDatabase::GetBgmVolume()
{
	return Volume;
}

/////////////////////////////////////////////////////////////////
//
//	BGM音量の設定
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
//	終了処理
//
void CBgmDatabase::Close()
{
	// あと始末
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