#pragma once
#include "LoadSoundFile.h"
#include<vector>

//-----------------------------------------------------------
//
//	WaveFile�������T�E���h���\�[�X�ǂݍ���
//
//------------------------------------------------------------
class CLoadWave : public CLoadSoundFile
{
public:
	CLoadWave(char* soundlistnumb,bool Loopflag);
	~CLoadWave();

	void LoadFormat();
	void Close();

	XAUDIO2_BUFFER PreloadBuffer();
	XAUDIO2_BUFFER StreamloadBuffer();
	
	// WaveFile�p�֐�
	std::size_t ReadDataRaw(const std::size_t start, const std::size_t sample, void* buffer);
	XAUDIO2_BUFFER CLoadWave::UpdateBuiffer(IXAudio2SourceVoice* const voice);

private:

	std::vector<float> primaryMixed = { 0 };
	std::vector< float > secondaryMixed = { 0 };

};

