#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const float GROUND = 32768.0f;
const float MAXPLUS = 65536.0f;
const float MIN = 0.0f;

/* Wave�t�@�C���p�̍\���� */

//formatchunk�̃f�[�^�\��
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

// datachunk�̃f�[�^�\��
struct Data_CHUNK
{
	char datachunkID[4];
	long chunkSize;
	short data;
};

// Wave�t�@�C���̃f�[�^�\��
struct WAVE_FORMAT
{
	// RIFF
	char chunkID[4];
	long chunksize;
	char FormType[4];

	FMT_CHUNK fmtchunk;
	Data_CHUNK datachunk;
};

// ���m���������f�[�^�̃f�[�^�\��
struct MONO_PCM
{
	int fs;			// �W�{�����g��
	int bits;		// �ʎq�����x
	int length;		// �f�[�^��
	double *sounddata;	// �{�̃f�[�^
};



///////////////////////////////////////////////////////////////
//
//	CWaveDataOperater
//		.wav�̊Ǘ��p
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
	//	Wave�t�@�C���̓ǂݍ���
	//
	void monoWaveRead(char *filename);


	/////////////////////////////////////////////////////////
	//
	//	DFT(���U�t�[���G�ϊ�)
	//
	//void DFTConversion(MONO_PCM pcm , Imaginary);

};

