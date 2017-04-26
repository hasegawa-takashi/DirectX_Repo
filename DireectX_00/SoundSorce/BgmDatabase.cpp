#include "BgmDatabase.h"

#include "LoadWave.h"

CBgmDatabase::CBgmDatabase()
{
	CreateBgmVoice();
}


CBgmDatabase::~CBgmDatabase()
{
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
void CBgmDatabase::Play(int BgmListNumb)
{
	HRESULT hr;

	if (FAILED(hr = m_BgmVoices[BgmListNumb]->Start() ))
	{
		
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