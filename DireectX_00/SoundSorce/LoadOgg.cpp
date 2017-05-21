#include "LoadOgg.h"



CLoadOgg::CLoadOgg()
{
}


CLoadOgg::~CLoadOgg()
{
}

void CLoadOgg::LoadOggFile(char* filename)
{

	
	
	// oggfileを開く
	if (ov_fopen(filename, &m_ovf))
	{
		// オープン失敗
		return;
	}

	// oggvorbisfile情報を取得
	vorbis_info* vi = ov_info(&m_ovf,-1);

	m_waveformat.wFormatTag = WAVE_FORMAT_PCM;
	m_waveformat.nChannels = vi->channels;
	m_waveformat.nSamplesPerSec = vi->rate;
	m_waveformat.nAvgBytesPerSec = vi->rate * vi->channels * 2;
	m_waveformat.nBlockAlign = vi->channels * 2;
	m_waveformat.wBitsPerSample = 16;
	m_waveformat.cbSize = sizeof(WAVEFORMATEX);

	DWORD decodesize = static_cast<DWORD>(ov_pcm_total(&m_ovf, -1) * vi->channels * 2);

	char* playbuf = NULL;
	playbuf = new char[decodesize];

	DWORD totalReadSize = 0;
	int bitstream;

	while (totalReadSize < decodesize)
	{
		LONG readsize = ov_read(&m_ovf,playbuf + totalReadSize,decodesize - totalReadSize,0,2,1,&bitstream);

		if (readsize == 0)
		{
			break;
		}

		totalReadSize += readsize;

	}


	ov_clear(&m_ovf);

	delete[] playbuf;


}

WAVEFORMATEX* CLoadOgg::GetWaveFormat()
{
	return &m_waveformat;
}