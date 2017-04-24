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

	void PreparationBuffer(XAUDIO2_BUFFER& buffer);
	void UpdateBuiffer(IXAudio2SourceVoice* voice , XAUDIO2_BUFFER& buffer);

private:
	void Close();

private:

	FILE* fp = NULL;
	WAVEFORMATEX m_waveformat;
	long m_firstSampleOffSet;
	std::size_t m_dataChunkSize;
	std::size_t m_dataChunkSample;
	
	// �t�H�[�}�b�g�����擾�ς݂�
	bool m_hasGotWaveFormat;

	// Buffer�ɕK�v�ȏ��
	std::size_t nextFirstSample = { 0 };
	std::size_t submitTimes		= { 0 };
	std::size_t bufferSample	= { 0 };

	// ���݂̃o�b�t�@
	std::vector<float> primaryLeft  = { 0 };
	std::vector<float> primaryRight = { 0 };
	std::vector<float> primaryMixed = { 0 };

	// ���̃o�b�t�@
	std::vector< float > secondaryLeft  = { 0 };
	std::vector< float > secondaryRight = { 0 };
	std::vector< float > secondaryMixed = { 0 };


};

