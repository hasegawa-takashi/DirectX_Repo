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
		m_VoiceData[loop].SourceWaveFormat = new CLoadWave(bgmdata::BGMName[loop]);
		m_VoiceData[loop].Voice = NULL;
	}

	// SouceVoiceの作成
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		WAVEFORMATEX* waveformat = m_VoiceData[loop].SourceWaveFormat->GetWaveFormat();
		GetXAudio2Mgr()->SetXAudio2SouceVoice(&m_VoiceData[loop].Voice, *waveformat);
	}

	// バッファの設定
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		m_VoiceData[loop].Voice->SubmitSourceBuffer(
			&m_VoiceData[loop].SourceWaveFormat->PreparationBuffer() );
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
		
		XAUDIO2_BUFFER buffer = m_VoiceData[loop].SourceWaveFormat->UpdateBuiffer( m_VoiceData[loop].Voice );

		// ループ再生
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
//	BGMの再生
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
//	BGMの再生
//
void CBgmDatabase::Play(int BgmListNumb)
{
	m_VoiceData[BgmListNumb].Voice->Start();
}


/////////////////////////////////////////////////////////////////
//
//	BGMの停止[BGMを全停止]
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
		m_VoiceData[BgmListNumb].Voice->Stop();
	}

}

/////////////////////////////////////////////////////////////////
//
//	BGM音量の取得
//
float CBgmDatabase::GetVolume()
{
	return Volume;
}

/////////////////////////////////////////////////////////////////
//
//	BGM音量の設定
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
//	終了処理
//
void CBgmDatabase::Close()
{
	// あと始末
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
//	フェードアウト
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
//	フェードイン
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