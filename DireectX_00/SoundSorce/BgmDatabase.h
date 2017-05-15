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
		Sound2,
		MAX_BGM,
	};

	static char* BGMName[bgmdata::MAX_BGM] =
	{
		"../data/Sound/Bgm/test.wav",
		"../data/Sound/Bgm/test2.wav",
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

	float GetBgmVolume();
	void SetBgmVolume(float Vol);

	void FadeOut(int BgmListNumb);
	void FadeIn(int BgmListNumb);
	
private:

	void Close();
	void CreateSourceVoice();

	SoundData* m_BgmData[bgmdata::MAX_BGM];				// SoundSorce
	std::function< void() > Soundfunc;					// Bgm‚Ìfunc
	float Volume = 1.0f;								// ‘S‘ÌVol
	
	bool m_Fade = false;
};

