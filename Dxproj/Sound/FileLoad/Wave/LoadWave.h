#pragma once
#include "../LoadSoundFile.h"
#include"../..\XAudio2/XAudio2Interface/XAudioInterface.h"
#include<vector>

//-----------------------------------------------------------
//
//	WaveFileを扱うサウンドリソース読み込み
//
//------------------------------------------------------------
class CLoadWave : public CLoadSoundFile
{
public:
	CLoadWave(std::string soundlistnumb,bool Loopflag);
	~CLoadWave();

	void LoadFormat();
	void Close();

	XAUDIO2_BUFFER PreloadBuffer();
	XAUDIO2_BUFFER StreamloadBuffer();
	
	virtual WAVEFORMATEX* GetWaveFormat() { return &m_SoundResouce.Waveformat; };

	virtual std::size_t ReadDataRaw(std::size_t start, std::size_t sample, void* buffer);
	virtual XAUDIO2_BUFFER UpdateBuffer(IXAudio2SourceVoice* voice);

	std::vector<float> GetPrimaryBuffer();

	bool GetNextbufferTime(IXAudio2SourceVoice* voice);

private:

	char* m_PresetSoundName;
	SoundResources m_SoundResouce;

	std::vector<float> primaryMixed = { 0 };
	std::vector< float > secondaryMixed = { 0 };


};

