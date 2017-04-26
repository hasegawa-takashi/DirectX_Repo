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

	IXAudio2SourceVoice* m_BgmVoices[bgmdata::MAX_BGM];	// BGMSourceVoice�̔z��
	VoiceCallback m_voicecallback;						// BGM��CallBack *BGM�𑽏d�Đ����Ȃ��O�� 
	CLoadWave* m_sourceWaveFormat[bgmdata::MAX_BGM];	// WaveForamt�̔z�� 
	float Volume;											// �S��Vol

};

