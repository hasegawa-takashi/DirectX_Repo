#pragma once

#include<XAudio2.h>
#include<vector>
#include<functional>
#include <iostream>

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
	void Play(int BgmListNumb,bool fadein);
	void Stop();
	void Stop(int BgmListNumb , bool fadeout);

	void Update();

	void Close();


	float GetBgmVolume();
	void SetBgmVolume(float Vol);

	void FadeOut(int BgmListNumb);
	void FadeIn(int BgmListNumb);
	
	void PitchRate(int BgmListNumb, float PitchRate );

private:
	void CreateSourceVoice();

	IXAudio2SourceVoice* m_BgmVoices[bgmdata::MAX_BGM];	// BGMSourceVoiceの配列
	VoiceCallback m_voicecallback;						// BGMのCallBack *BGMを多重再生しない前提 
	CLoadWave* m_sourceWaveFormat[bgmdata::MAX_BGM];	// WaveForamtの配列 
	std::function< void() > Soundfunc;					// Bgmのfunc
	float Volume = 1.0f;								// 全体Vol
	bool m_Fade = false;
};

