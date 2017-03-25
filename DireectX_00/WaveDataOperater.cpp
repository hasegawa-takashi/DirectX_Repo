#include "WaveDataOperater.h"
#include"Window.h"
#include<iostream>

CWaveDataOperater::CWaveDataOperater()
{
	fp = NULL;
}

CWaveDataOperater::CWaveDataOperater(char *filenpath)
{
	fp = NULL;
	monoWaveRead(filenpath);

}


CWaveDataOperater::~CWaveDataOperater()
{
}

/////////////////////////////////////////////////////////
//
//	Waveファイルの読み込み
//
void CWaveDataOperater::monoWaveRead(char *filename)
{
	WAVE_FORMAT waveformat;

	fp = fopen(filename,"rb");

	if (!fp)
	{
		// 失敗処理
		GetWinMgr()->MessageBoxA("ファイルの読み込みの失敗");
		return;
	}
	
	// ヘッダの読み込み
	fread(&waveformat,sizeof(WAVE_FORMAT),1,fp);
	data_beg = ftell(fp);

	// 形式のチェック
	if((memcmp(&waveformat.chunkID, "RIFF", 4) != 0)
		|| (memcmp(&waveformat.FormType, "WAVE", 4) != 0)
		|| (waveformat.fmtchunk.WaveFormatType != 1)) {

		GetWinMgr()->MessageBoxA("ファイルの読み込みの失敗");
		return;
	}

	//dataチャンク
	if (memcmp(&waveformat.datachunk.datachunkID, "data", 4) != 0)
	{

		unsigned int chunk_ID_temp[4];
		unsigned int chunksize_temp;

		fseek(fp,12+8+waveformat.fmtchunk.chunksize,SEEK_SET);

		fread(chunk_ID_temp,1,4,fp);

		while (memcmp(chunk_ID_temp,"data",4)!= 0)
		{
			fread(&chunksize_temp,4,1,fp);
			fseek(fp,chunksize_temp,SEEK_CUR);
			fread(chunk_ID_temp, 1, 4, fp);
		}

		fread(&chunksize_temp,4,1,fp);
		data_beg = ftell(fp);

		//datachunk更新
		for (int i = 0; i < 4; i++)
		{
			waveformat.datachunk.datachunkID[i] = chunk_ID_temp[i];
		}
		waveformat.datachunk.chunkSize = chunksize_temp;

	}

	fclose(fp);

}
