#pragma once
#include<xaudio2.h>
#include<cstdio>
#include<stdint.h>

class CLoadWave
{
public:
	CLoadWave(char* filepass);
	~CLoadWave();

	WAVEFORMATEX* GetWaveFormat();
	std::size_t GetSamples();
	std::size_t ReadRaw(const std::size_t start,const std::size_t sample,void* buffer );
	std::size_t ReadNormalized(const std::size_t start, const std::size_t samples, float * left, float * right);

private:
	void Close();

private:

	FILE* fp = NULL;
	WAVEFORMATEX m_waveformat;
	long m_firstSampleOffSet;
	std::size_t m_dataChunkSize;
	std::size_t m_dataChunkSample;
	
	// フォーマット情報を取得済みか
	bool m_hasGotWaveFormat;

};

