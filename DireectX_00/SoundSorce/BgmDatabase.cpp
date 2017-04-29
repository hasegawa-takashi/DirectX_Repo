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
		m_BgmVoices[loop]->SubmitSourceBuffer( &m_sourceWaveFormat[loop]->PreparationBuffer() );
	}

	Soundfunc = []() {};
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

	if (Soundfunc != NULL)
	{
		Soundfunc();
	}

}

/////////////////////////////////////////////////////////////////
//
//	BGMの再生
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
//	BGMの再生
//
void CBgmDatabase::Play(int BgmListNumb)
{
	m_BgmVoices[BgmListNumb]->Start();
}


/////////////////////////////////////////////////////////////////
//
//	BGMの停止[BGMを全停止]
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
//	BGMの停止[BGMを選択停止]
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

/////////////////////////////////////////////////////////////////
//
//	フェードアウト
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
//	フェードイン
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
//	ピッチレートの変更関数
//
void CBgmDatabase::PitchRate(int BgmListNumb,float PitchRate)
{
	m_BgmVoices[0]->SetFrequencyRatio(PitchRate);
}