#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const float GROUND = 32768.0f;
const float MAXPLUS = 65536.0f;
const float MIN = 0.0f;

/* Waveファイル用の構造体 */

//formatchunkのデータ構造
struct FMT_CHUNK
{
	char chunkID[4];
	long chunksize;
	short WaveFormatType;
	short Channel;
	long samplesPersec;
	long BytesPerSec;
	short BlockSize;
	short BitsPerSample;
};

// datachunkのデータ構造
struct Data_CHUNK
{
	char datachunkID[4];
	long chunkSize;
	short data;
};

// Waveファイルのデータ構造
struct WAVE_FORMAT
{
	// RIFF
	char chunkID[4];
	long chunksize;
	char FormType[4];

	FMT_CHUNK fmtchunk;
	Data_CHUNK datachunk;
};

// モノラル音声データのデータ構造
struct MONO_PCM
{
	int fs;			// 標本化周波数
	int bits;		// 量子化制度
	int length;		// データ長
	double *sounddata;	// 本体データ
};



///////////////////////////////////////////////////////////////
//
//	CWaveDataOperater
//		.wavの管理用
//
//
///////////////////////////////////////////////////////////////
class CWaveDataOperater
{

private:
	FILE *fp;
	WAVE_FORMAT waveformat;
	MONO_PCM pcm;
	unsigned int data_beg;

public:
	CWaveDataOperater();
	CWaveDataOperater(char *filenpath);
	~CWaveDataOperater();

	/////////////////////////////////////////////////////////
	//
	//	Waveファイルの読み込み
	//
	void monoWaveRead(char *filename);


	/////////////////////////////////////////////////////////
	//
	//	DFT(離散フーリエ変換)
	//
	//void DFTConversion(MONO_PCM pcm , Imaginary);

};

