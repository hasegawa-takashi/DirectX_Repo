#pragma once

#include<XAudio2.h>
#include<vector>
#include<functional>
#include<iostream>

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

	float GetVolume();
	void SetMasterVolume(float Vol);

	void SetBgmVolume(int SetListNumb, float Vol) {};

	void FadeOut(int BgmListNumb);
	void FadeIn(int BgmListNumb);
	
	// エフェクト用
	void ChangeReverv(int ListNumb, float walltype, float roomsize);
	void OffReverv();
	void ChangeEcho(int ListNumb, float Delay, float feedback, float wetdry);
	void OffEcho();
	void ChangePitch(int ListNumb, float PitchRate);

private:

	void Close();
	void CreateSourceVoice();

	SoundData* m_VoiceData[bgmdata::MAX_BGM];				// SoundSorce
	
	std::function< void() > Soundfunc;					// Bgmのfunc
	float Volume = 1.0f;								// 全体Vol
	
	bool m_Fade = false;
};

