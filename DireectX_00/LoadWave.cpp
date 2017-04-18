#include "LoadWave.h"



CLoadWave::CLoadWave()
{
	OpenWave();
}


CLoadWave::~CLoadWave()
{
}

void CLoadWave::OpenWave()
{
	MMIOINFO info = { 0 };

	for (int loop = 0 ; loop < BGMList::MAX_BGM ; loop++)
	{
		mmio[loop] = mmioOpen( g_pszFileBGM[loop] ,&info , MMIO_READ);
	}

	MMCKINFO riff_chunk;
	riff_chunk.fccType = mmioFOURCC('W','A','V','E');
	for (int loop = 0; loop < BGMList::MAX_BGM; loop++)
	{
		mret[loop] = mmioDescend(mmio[loop], &riff_chunk, NULL, MMIO_FINDRIFF);
	}

	MMCKINFO chunk;
	chunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	for (int loop = 0; loop < BGMList::MAX_BGM; loop++)
	{
		mret[loop] = mmioDescend(mmio[loop], &chunk, &riff_chunk, MMIO_FINDCHUNK);
	}

	WAVEFORMAT format = { 0 };
	{
		DWORD size[BGMList::MAX_BGM];
		for (int loop = 0; loop < BGMList::MAX_BGM; loop++)
		{
			size[loop] = mmioRead(mmio[loop],(HPSTR)&format,chunk.cksize );
		}
	}

	chunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	for (int loop = 0; loop < BGMList::MAX_BGM; loop++)
	{
		mret[loop] = mmioDescend(mmio[loop], &chunk, &riff_chunk, MMIO_FINDCHUNK);
	}

}