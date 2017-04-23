#include "BgmDatabase.h"

#include "LoadWave.h"
#include"XAudio2Interface.h"
#include"SoundMgr.h"

CBgmDatabase::CBgmDatabase()
{
	CreateBgmVoice();
}


CBgmDatabase::~CBgmDatabase()
{
}

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
		GetSoundMgr()->SetXAudio2Souce(m_BgmVoices[loop], *waveformat);
	}

	// バッファの設定
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		XAUDIO2_BUFFER buffer = m_sourceWaveFormat[loop]->PreparationBuffer() ;
		m_BgmVoices[loop]->SubmitSourceBuffer(&buffer);
	}

}

void CBgmDatabase::Update()
{
	// バッファの設定
	for (int loop = 0; loop < bgmdata::MAX_BGM; ++loop)
	{
		XAUDIO2_BUFFER buffer = m_sourceWaveFormat[loop]->UpdateBuiffer(m_BgmVoices[loop]);
		m_BgmVoices[loop]->SubmitSourceBuffer(&buffer);
	}
}

void CBgmDatabase::Play(int BgmListNumb)
{
	HRESULT hr;

	if (FAILED(hr = m_BgmVoices[BgmListNumb]->Start()))
	{
		
	}
}
