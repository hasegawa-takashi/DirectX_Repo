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
//		.wav�̊Ǘ��p
//
//
///////////////////////////////////////////////////////////////
class CWaveDataOperater
{

private:



	/* Wave�t�@�C���p�̍\���� */

	// ���m���������f�[�^�̃f�[�^�\��
	struct MONO_PCM
	{
		int fs;			// �W�{�����g��
		int bits;		// �ʎq�����x
		int length;		// �f�[�^��
		double *sounddata;	// �{�̃f�[�^
	};

	// RIFF�`�����N�̃f�[�^�\��
	struct RIFF_CHUNK
	{
		char chunkID[4];
		long chunksize;
		char FormType[4];
	};

	//formatchunk�̃f�[�^�\��
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
		RIFF_CHUNK riffchunk;
		FMT_CHUNK fmtchunk;
		Data_CHUNK datachunk;
	};


public:
	CWaveDataOperater();
	~CWaveDataOperater();

	/////////////////////////////////////////////////////////
	//
	//	Wave�t�@�C���̓ǂݍ���
	//
	void monoWaveRead(MONO_PCM *pcm, char *filename);


	/////////////////////////////////////////////////////////
	//
	//	Wave�t�@�C���̏����o��
	//
	void monoWaveWrite(MONO_PCM *pcm, char *filename);



};

