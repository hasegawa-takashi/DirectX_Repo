#pragma once

#include"SoundMgr.h"

enum BGMList
{
	Title,
	MAX_BGM
};

class CBGM
{
public:
	CBGM();
	~CBGM();


private:

	void ReadWaveFile();
	void PlayBGM(BGMList);


	IXAudio2SourceVoice* m_Voice[MAX_BGM];

};
