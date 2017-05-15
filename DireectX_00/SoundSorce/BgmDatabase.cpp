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
//	SouceVoiceの作成
//
void CBgmDatabase::CreateSourceVoice()
{
	// 全BGMのLoad
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_BgmData[loop]->SourceWaveFormat = new CLoadWave(bgmdata::BGMName[loop]);
		m_BgmData[loop]->Voice = NULL;
	}

	// SouceVoiceの作成
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		WAVEFORMATEX* waveformat = m_BgmData[loop]->SourceWaveFormat->GetWaveFormat();
		GetXAudio2Mgr()->SetXAudio2SouceVoice(&m_BgmData[loop]->Voice, *waveformat);
	}

	// バッファの設定
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_BgmData[loop]->Voice->SubmitSourceBuffer(
			&m_BgmData[loop]->SourceWaveFormat->PreparationBuffer() );
	}

	Soundfunc = nullptr;
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
		//XAUDIO2_BUFFER buffer = m_sourceWaveFormat[loop]->UpdateBuiffer(m_BgmVoices[loop]);
		
		XAUDIO2_BUFFER buffer = m_BgmData[loop]->SourceWaveFormat->UpdateBuiffer( m_BgmData[loop]->Voice );

		// ループ再生
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
//	BGMの再生
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
//	BGMの再生
//
void CBgmDatabase::Play(int BgmListNumb)
{
	m_BgmData[BgmListNumb]->Voice->Start();
}


/////////////////////////////////////////////////////////////////
//
//	BGMの停止[BGMを全停止]
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
//	BGMの停止[BGMを選択停止]
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
//	終了処理
//
void CBgmDatabase::Close()
{
	// あと始末
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
//	フェードアウト
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
//	フェードイン
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
