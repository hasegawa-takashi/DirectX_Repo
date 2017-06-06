#include "LoadOgg.h"

CLoadOgg::CLoadOgg(char* soundlistnumb, bool Loopflag)
{
	m_SoundResouce.m_DataChunkSample = NULL;
	m_SoundResouce.m_DataChunkSize = NULL;
	m_SoundResouce.m_firstSampleOffSet = NULL;
	m_SoundResouce.m_HasGotWaveFormat = false;
	m_SoundResouce.m_Waveformat = {};
	m_SoundResouce.m_LoopSound = Loopflag;
	m_PresetSoundName = soundlistnumb;

	LoadFormat();
}


CLoadOgg::~CLoadOgg()
{
}

void CLoadOgg::LoadFormat()
{
	// oggfileを開く
	if (ov_fopen(m_PresetSoundName, &m_Ovf))
	{
		// オープン失敗
		return;
	}

	// oggvorbisfile情報を取得
	vorbis_info* vi = ov_info(&m_Ovf, -1);

	m_SoundResouce.m_Waveformat.wFormatTag = WAVE_FORMAT_PCM;
	m_SoundResouce.m_Waveformat.nChannels = vi->channels;
	m_SoundResouce.m_Waveformat.nSamplesPerSec = vi->rate;
	m_SoundResouce.m_Waveformat.nAvgBytesPerSec = vi->rate * vi->channels * 2;
	m_SoundResouce.m_Waveformat.nBlockAlign = vi->channels * 2;
	m_SoundResouce.m_Waveformat.wBitsPerSample = 16;
	m_SoundResouce.m_Waveformat.cbSize = sizeof(WAVEFORMATEX);

	ov_clear(&m_Ovf);
}

void CLoadOgg::Close()
{

}

XAUDIO2_BUFFER CLoadOgg::PreloadBuffer()
{
	// oggfileを開く
	if (ov_fopen(m_PresetSoundName, &m_Ovf))
	{
		// オープン失敗
		return;
	}

	// oggvorbisfile情報を取得
	vorbis_info* vi = ov_info(&m_Ovf, -1);

	DWORD decodesize = static_cast<DWORD>(ov_pcm_total(&m_Ovf, -1) * vi->channels * 2);

	char* playbuf = NULL;
	playbuf = new char[decodesize];

	DWORD totalReadSize = 0;
	int bitstream;

	while (totalReadSize < decodesize)
	{
		LONG readsize = ov_read(&m_Ovf, playbuf + totalReadSize, decodesize - totalReadSize, 0, 2, 1, &bitstream);

		if (readsize == 0)
		{
			break;
		}
		totalReadSize += readsize;
	}

	ov_clear(&m_Ovf);

	delete[] playbuf;

}

XAUDIO2_BUFFER CLoadOgg::StreamloadBuffer()
{
	
}

std::size_t CLoadOgg::ReadDataRaw(const std::size_t start, const std::size_t sample, void* buffer)
{
	
	//ov_open_callbacks();

}