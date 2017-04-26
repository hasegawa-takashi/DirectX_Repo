#pragma once

#include<XAudio2.h>
#include<vector>

#include"LoadWave.h"
#include"XAudio2Interface.h"

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

	float GetBgmVolume();
	void SetBgmVolume(float Vol);

	void Close();

private:
	void CreateBgmVoice();

	IXAudio2SourceVoice* m_BgmVoices[bgmdata::MAX_BGM];	// BGMSourceVoiceの配列
	VoiceCallback m_voicecallback;						// BGMのCallBack *BGMを多重再生しない前提 
	CLoadWave* m_sourceWaveFormat[bgmdata::MAX_BGM];	// WaveForamtの配列 
	float Volume;											// 全体Vol

};

