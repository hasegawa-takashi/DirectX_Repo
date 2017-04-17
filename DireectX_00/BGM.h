#pragma once

#include"SoundMgr.h"

namespace BGMList
{
	enum {
		Title,
		MAX_BGM
	};
}

class CBGM
{
public:
	CBGM();
	~CBGM();

	

	void PlayBGM(int bgmlist);
	void SetBGMVol(float vol);

private:

	void ReadWaveFile();
	void Close();
	float GetBGMVol();
	

	IXAudio2SourceVoice* m_Voice[BGMList::MAX_BGM];	// サウンドデータ
	XAUDIO2_BUFFER buffer;
	float Volume;								// BGM全体の音量0


};
