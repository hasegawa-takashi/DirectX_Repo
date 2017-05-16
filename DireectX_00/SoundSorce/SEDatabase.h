#pragma once


#include<XAudio2.h>
#include<vector>
#include<functional>
#include<iostream>
#include<XAPOFX.h>

#include"LoadWave.h"
#include"XAudio2Interface.h"

#pragma comment(lib,"XAPOFX.lib")

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
	void Play(int SeListNumb,bool fadein);
	void Stop();
	void Stop(int SeListNumb);

	void Update();
	
	float GetSeVolume();
	void SetMasterVolume(float Vol);
	
	void SetSeVolume(int SetListNumb,float Vol);

	void FadeOut(int BgmListNumb);
	void FadeIn(int BgmListNumb);

private:
	void Close();
	void CreateSourceVoice();

	SoundData* m_SeData[sedata::MAX_SE];				// SoundSorce
	std::function< void() > Soundfunc;					// Bgm‚Ìfunc
	float Volume = 1.0f;								// ‘S‘ÌVol

};

