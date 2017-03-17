#include "WaveDataOperater.h"



CWaveDataOperater::CWaveDataOperater()
{
}


CWaveDataOperater::~CWaveDataOperater()
{
}

/////////////////////////////////////////////////////////
//
//	Waveファイルの読み込み
//
void CWaveDataOperater::monoWaveRead(MONO_PCM *pcm, char *filename)
{
	FILE *fp;
	WAVE_FORMAT waveformat;

	fp = fopen(filename,"rb");

	if (!fp)
	{
		// 失敗処理
		// MesseageBoxでもok
		return;
	}

	//Riffdhunkの読み込み
	fread(waveformat.riffchunk.chunkID,1,4,fp);
	fread(&waveformat.riffchunk.chunksize, 4, 1, fp);
	fread(waveformat.riffchunk.FormType, 1, 4, fp);

	//Formatchunkの読み込み
	fread(waveformat.fmtchunk.chunkID,1,4,fp);
	fread(&waveformat.fmtchunk.chunksize, 4, 1, fp);
	fread(&waveformat.fmtchunk.WaveFormType, 2, 1, fp);
	fread(&waveformat.fmtchunk.Channel, 2, 1, fp);
	fread(&waveformat.fmtchunk.samplesPersec, 4, 1, fp);
	fread(&waveformat.fmtchunk.BytesPerSec, 4, 1, fp);
	fread(&waveformat.fmtchunk.BlockSize, 2, 1, fp);
	fread(&waveformat.fmtchunk.BitsPerSample, 2, 1, fp);

	// 音データの読み込み
	fread(waveformat.datachunk.datachunkID,1,4,fp);
	fread(&waveformat.datachunk.chunkSize, 4, 1, fp);

	pcm->fs = waveformat.fmtchunk.samplesPersec;
	pcm->bits = waveformat.fmtchunk.BitsPerSample;
	pcm->length = waveformat.datachunk.chunkSize;
	pcm->sounddata = new double(pcm->length);



	// datachunkの読み込み
	short data;
	for (int loop = 0;loop < pcm->length ; loop++ )
	{
		fread(&data,2,1,fp);
		pcm->sounddata[loop] = (double)data / GROUND;
	}

	fclose(fp);

}


/////////////////////////////////////////////////////////
//
//	Waveファイルの書き出し
//
void CWaveDataOperater::monoWaveWrite(MONO_PCM *pcm, char *filename)
{
	FILE *fp;
	int loop;
	WAVE_FORMAT waveformat;

	strcpy(waveformat.riffchunk.chunkID,"RIFF");
	waveformat.riffchunk.chunksize = 36 + pcm->length * 2;
	strcpy(waveformat.riffchunk.FormType,"WAVE");

	strcpy(waveformat.fmtchunk.chunkID,"fmt ");
	waveformat.fmtchunk.chunksize = 16;
	waveformat.fmtchunk.WaveFormType = 1;	// PCMの場合は1
	waveformat.fmtchunk.Channel = 2;		// ステレオ2 モノラル1
	waveformat.fmtchunk.samplesPersec = pcm->fs;
	waveformat.fmtchunk.BytesPerSec = (pcm->fs*pcm->bits)/8;
	waveformat.fmtchunk.BlockSize = pcm->bits / 8;
	waveformat.fmtchunk.BitsPerSample = pcm->bits;

	strcpy(waveformat.datachunk.datachunkID,"data");
	waveformat.datachunk.chunkSize = pcm->length * 2;

	fp = fopen(filename,"wb");

	if (!fp)
	{
		// 生成ミス
	}


	fwrite(waveformat.fmtchunk.chunkID,1,4,fp);

	//Riffdhunkの読み込み
	fwrite(waveformat.riffchunk.chunkID, 1, 4, fp);
	fwrite(&waveformat.riffchunk.chunksize, 4, 1, fp);
	fwrite(waveformat.riffchunk.FormType, 1, 4, fp);

	//Formatchunkの読み込み
	fwrite(waveformat.fmtchunk.chunkID, 1, 4, fp);
	fwrite(&waveformat.fmtchunk.chunksize, 4, 1, fp);
	fwrite(&waveformat.fmtchunk.WaveFormType, 2, 1, fp);
	fwrite(&waveformat.fmtchunk.Channel, 2, 1, fp);
	fwrite(&waveformat.fmtchunk.samplesPersec, 4, 1, fp);
	fwrite(&waveformat.fmtchunk.BytesPerSec, 4, 1, fp);
	fwrite(&waveformat.fmtchunk.BlockSize, 2, 1, fp);
	fwrite(&waveformat.fmtchunk.BitsPerSample, 2, 1, fp);

	// 音データの読み込み
	fwrite(waveformat.datachunk.datachunkID, 1, 4, fp);
	fwrite(&waveformat.datachunk.chunkSize, 4, 1, fp);

	pcm->fs = waveformat.fmtchunk.samplesPersec;
	pcm->bits = waveformat.fmtchunk.BitsPerSample;
	pcm->length = waveformat.datachunk.chunkSize;
	pcm->sounddata = new double(pcm->length);



	// datachunkの読み込み
	short data;
	for (int loop = 0; loop < pcm->length; loop++)
	{
		fwrite(&data, 2, 1, fp);
		pcm->sounddata[loop] = (double)data / GROUND;
	}


	fclose(fp);

}