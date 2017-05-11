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

	void Stop(int SeListNumb);

	void Update();

	void Close();

	float GetSeVolume();

	void SetSeVolume(float Vol);
	
	void PitchRate(int BgmListNumb, float PitchRate);
	
	void SetReverbSize(float walltype , float roomsize);
	void offsetReverbSize();

private:

	void CreateSourceVoice();
	void CreateVoiceEffect();

	IXAudio2SourceVoice* m_SeVoices[sedata::MAX_SE];	// BGMSourceVoiceの配列
	VoiceCallback m_voicecallback;						// BGMのCallBack *BGMを多重再生しない前提 
	CLoadWave* m_sourceWaveFormat[sedata::MAX_SE];		// WaveForamtの配列

	// XAPOFX
	IUnknown* m_reverb;
	XAUDIO2_EFFECT_CHAIN m_chain;
	XAUDIO2_EFFECT_DESCRIPTOR m_desc;
	FXREVERB_PARAMETERS m_Reverbpram;

	std::function< void() > Soundfunc;					// Bgmのfunc
	float Volume = 1.0f;								// 全体Vol

};

