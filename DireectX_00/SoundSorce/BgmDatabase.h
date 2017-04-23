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

	void BufferUpdate();

private:
	void CreateBgmVoice();
	void CreateBuffer();

	IXAudio2SourceVoice* m_BgmVoices[bgmdata::MAX_BGM];	// BGMSourceVoice‚Ì”z—ñ
	CLoadWave* m_sourceWaveFormat[bgmdata::MAX_BGM];	// WaveForamt‚Ì”z—ñ 
	int Volume;											// ‘S‘ÌVol


	std::size_t nextFirstSample[bgmdata::MAX_BGM] = { 0 };
	std::size_t submitTimes[bgmdata::MAX_BGM] = { 0 };
	std::size_t bufferSample[bgmdata::MAX_BGM] = {0};

	std::vector<float> primaryLeft[bgmdata::MAX_BGM];
	std::vector<float> primaryRight[bgmdata::MAX_BGM];
	std::vector<float> primaryMixed[bgmdata::MAX_BGM];

	std::vector< float > secondaryLeft[bgmdata::MAX_BGM];
	std::vector< float > secondaryRight[bgmdata::MAX_BGM];
	std::vector< float > secondaryMixed[bgmdata::MAX_BGM];



};

