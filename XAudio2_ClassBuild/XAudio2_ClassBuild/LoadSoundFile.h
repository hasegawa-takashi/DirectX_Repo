#pragma once

#include"Sound.h"

struct SoundResouces
{
	WAVEFORMATEX m_Waveformat;

	std::size_t m_DataChunkSize;
	std::size_t m_DataChunkSample;
	long m_firstSampleOffSet;
	
	// フォーマット情報を取得済みか
	bool m_HasGotWaveFormat;
	bool m_LoopSound;

	// Buffer情報
	std::size_t m_NextFirstSample = { 0 };
	std::size_t m_SubmitTimes = { 0 };
	std::size_t m_BufferSample = { 0 };
};

//==================================================
//
//	各種リソースのベースとなる部分
//
//==================================================
class CLoadSoundFile
{
public:
	CLoadSoundFile() {};
	~CLoadSoundFile() {};

	virtual void LoadFormat() {};
	virtual void Close() {};
	virtual XAUDIO2_BUFFER PreloadBuffer() {};
	virtual XAUDIO2_BUFFER StreamloadBuffer() {};

	WAVEFORMATEX GetWaveFormat() { return m_SoundResouce.m_Waveformat; };
	
protected:

	char* m_PresetSoundName;
	SoundResouces m_SoundResouce;

};

