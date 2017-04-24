#pragma once

#include<XAudio2.h>
#include<vector>
#include"LoadWave.h"

namespace bgmdata {
	enum BgmNameList
	{
		Sound1,
		MAX_BGM,
	};


	static char* BGMName[bgmdata::MAX_BGM] =
	{
		"../data/Sound/Bgm/test.wav",
	};

}

class CBgmDatabase
{
public:

	CBgmDatabase();
	~CBgmDatabase();

	void Play(int BgmListNumb);

	void Update();

	void Close();

private:
	void CreateBgmVoice();

	IXAudio2SourceVoice* m_BgmVoices[bgmdata::MAX_BGM];	// BGMSourceVoiceの配列
	XAUDIO2_BUFFER m_AudioBuffer[bgmdata::MAX_BGM] = {0};
	CLoadWave* m_sourceWaveFormat[bgmdata::MAX_BGM];	// WaveForamtの配列 
	int Volume;											// 全体Vol

};

