#pragma once


#include<XAudio2.h>
#include<vector>
#include<functional>
#include<iostream>

#include"VoiceEffect.h"
#include"LoadWave.h"
#include"XAudio2Interface.h"


namespace sedata {
	enum SeNameList
	{
		SE1,
		MAX_SE,
	};

	static char* SEName[sedata::MAX_SE] =
	{
		"../data/Sound/Bgm/test.wav",
	};
}


class CSEDatabase
{
public:
	CSEDatabase();
	~CSEDatabase();

	void Play(int SeListNumb);
	void Play(int SeListNumb, bool fadein);
	void Play(int SeListNumb, bool fadein, D3DXMATRIX matrix);

	void Stop(int SeListNumb, bool fadeout);

	void Update();
	
	float GetVolume();
	void SetMasterVolume(float Vol);
	
	void SetSeVolume(int SetListNumb,float Vol);

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

	SoundData m_VoiceData[sedata::MAX_SE];				// SoundSorce
	std::function< void() > Soundfunc;					// Bgmのfunc
	float Volume = 1.0f;								// 全体Vol

};

