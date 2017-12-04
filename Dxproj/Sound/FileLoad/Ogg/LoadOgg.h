#pragma once
#include "../LoadSoundFile.h"
#include"../../Sound.h"


//===========================================================
// TODO
//	OggÇì«Ç›çûÇﬁÉNÉâÉX
//		Ç‹Çæå`ÇæÇØÇ≈ñ¢äÆê¨		
//
//===========================================================
class CLoadOgg : public CLoadSoundFile
{
public:
	CLoadOgg(std::string soundlistnumb, bool Loopflag);
	~CLoadOgg();

	void LoadFormat();
	void Close();
	XAUDIO2_BUFFER PreloadBuffer(std::size_t first, std::size_t last);
	XAUDIO2_BUFFER StreamloadBuffer();

	std::size_t ReadDataRaw(const std::size_t start, const std::size_t sample, char* buffer);
	XAUDIO2_BUFFER UpdateBuffer(IXAudio2SourceVoice* voice) override;

	std::vector<float> GetPrimaryBuffer();
	// TODO ñ¢é¿ëï
	bool GetNextbufferTime(IXAudio2SourceVoice* voice) { return false; }

private:

	const int OGG_BUFFER_SIZE = 4096;
	char* m_Secondbuf;
	char* m_Playbuf;
	int m_BuffCnt;

	OggVorbis_File m_Ovf;
	DWORD m_TotalReadSize;
};

