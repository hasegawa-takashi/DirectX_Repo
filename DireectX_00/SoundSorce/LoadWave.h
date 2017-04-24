#pragma once
#include<xaudio2.h>
#include<cstdio>
#include<stdint.h>
#include<vector>

class CLoadWave
{
public:
	CLoadWave(char* filepass);
	~CLoadWave();

	WAVEFORMATEX* GetWaveFormat();
	std::size_t GetSamples();
	std::size_t ReadRaw(const std::size_t start,const std::size_t sample,void* buffer );
	std::size_t ReadNormalized(const std::size_t start, const std::size_t samples, float * left, float * right);

	XAUDIO2_BUFFER PreparationBuffer();
	XAUDIO2_BUFFER UpdateBuiffer(IXAudio2SourceVoice* voice);

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

	// Bufferに必要な情報
	std::size_t nextFirstSample = { 0 };
	std::size_t submitTimes		= { 0 };
	std::size_t bufferSample	= { 0 };

	// 現在のバッファ
	std::vector<float> primaryLeft  = { 0 };
	std::vector<float> primaryRight = { 0 };
	std::vector<float> primaryMixed = { 0 };

	// 次のバッファ
	std::vector< float > secondaryLeft  = { 0 };
	std::vector< float > secondaryRight = { 0 };
	std::vector< float > secondaryMixed = { 0 };


};

