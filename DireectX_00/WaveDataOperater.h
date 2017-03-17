#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const float GROUND = 32768.0f;
const float MAXPLUS = 65536.0f;
const float MIN = 0.0f;

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



	/* Waveファイル用の構造体 */

	// モノラル音声データのデータ構造
	struct MONO_PCM
	{
		int fs;			// 標本化周波数
		int bits;		// 量子化制度
		int length;		// データ長
		double *sounddata;	// 本体データ
	};

	// RIFFチャンクのデータ構造
	struct RIFF_CHUNK
	{
		char chunkID[4];
		long chunksize;
		char FormType[4];
	};

	//formatchunkのデータ構造
	struct FMT_CHUNK
	{
		char chunkID[4];
		long chunksize;
		short WaveFormType;
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
		RIFF_CHUNK riffchunk;
		FMT_CHUNK fmtchunk;
		Data_CHUNK datachunk;
	};


public:
	CWaveDataOperater();
	~CWaveDataOperater();

	/////////////////////////////////////////////////////////
	//
	//	Waveファイルの読み込み
	//
	void monoWaveRead(MONO_PCM *pcm, char *filename);


	/////////////////////////////////////////////////////////
	//
	//	Waveファイルの書き出し
	//
	void monoWaveWrite(MONO_PCM *pcm, char *filename);



};

