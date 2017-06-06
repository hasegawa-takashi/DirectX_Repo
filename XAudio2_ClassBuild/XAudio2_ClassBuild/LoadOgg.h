#pragma once
#include "LoadSoundFile.h"
#include"Sound.h"

class CLoadOgg : public CLoadSoundFile
{
public:
	CLoadOgg(char* soundlistnumb, bool Loopflag);
	~CLoadOgg();

	void LoadFormat();
	void Close();
	XAUDIO2_BUFFER PreloadBuffer();
	XAUDIO2_BUFFER StreamloadBuffer();

	std::size_t ReadDataRaw(const std::size_t start, const std::size_t sample, void* buffer);

private:
	OggVorbis_File m_Ovf;

};

