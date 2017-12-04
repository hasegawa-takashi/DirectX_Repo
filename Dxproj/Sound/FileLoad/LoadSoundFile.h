#pragma once

#include"../Sound.h"


struct SoundResources
{
	WAVEFORMATEX Waveformat;

	std::size_t DataChunkSize;
	std::size_t DataChunkSample;
	long firstSampleOffSet;
	
	int PlayTime;

	// �t�H�[�}�b�g�����擾�ς݂�
	bool HasGotWaveFormat;
	bool LoopSound;

	// Buffer���
	std::size_t NextFirstSample = { 0 };
	std::size_t SubmitTimes = { 0 };
	std::size_t BufferSample = { 0 };
};

//==================================================
//
//	�e�탊�\�[�X�̃x�[�X�ƂȂ镔��
//
//==================================================
class CLoadSoundFile
{
public:
	CLoadSoundFile() {}
	virtual ~CLoadSoundFile() {}

	virtual void LoadFormat() = 0;
	virtual void Close() = 0;
	virtual XAUDIO2_BUFFER PreloadBuffer(std::size_t first, std::size_t last) = 0;
	virtual XAUDIO2_BUFFER StreamloadBuffer() = 0;

	virtual WAVEFORMATEX* GetWaveFormat() { return &m_SoundResouce.Waveformat; };

	virtual std::size_t ReadDataRaw(std::size_t start, std::size_t sample, void* buffer) { return 0; }
	virtual XAUDIO2_BUFFER UpdateBuffer(IXAudio2SourceVoice* voice) = 0;

	virtual std::vector<float> GetPrimaryBuffer() = 0;
	size_t GetPrimaryBufferSize() { return primaryMixed.size(); }

	virtual bool GetNextbufferTime(IXAudio2SourceVoice* voice) = 0;

protected:

	char* m_PresetSoundName;
	SoundResources m_SoundResouce;
	bool m_BufferLoadflag;


	std::vector<float> primaryMixed = { 0 };
	std::vector< float > secondaryMixed = { 0 };



};

