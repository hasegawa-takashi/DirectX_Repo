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

	IXAudio2SourceVoice* m_BgmVoices[bgmdata::MAX_BGM];	// BGMSourceVoice‚Ì”z—ñ
	VoiceCallBack m_voicecallback;
	CLoadWave* m_sourceWaveFormat[bgmdata::MAX_BGM];	// WaveForamt‚Ì”z—ñ 
	int Volume;											// ‘S‘ÌVol

};

