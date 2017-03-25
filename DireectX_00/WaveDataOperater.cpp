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
//	Wave�t�@�C���̓ǂݍ���
//
void CWaveDataOperater::monoWaveRead(char *filename)
{
	WAVE_FORMAT waveformat;

	fp = fopen(filename,"rb");

	if (!fp)
	{
		// ���s����
		GetWinMgr()->MessageBoxA("�t�@�C���̓ǂݍ��݂̎��s");
		return;
	}
	
	// �w�b�_�̓ǂݍ���
	fread(&waveformat,sizeof(WAVE_FORMAT),1,fp);
	data_beg = ftell(fp);

	// �`���̃`�F�b�N
	if((memcmp(&waveformat.chunkID, "RIFF", 4) != 0)
		|| (memcmp(&waveformat.FormType, "WAVE", 4) != 0)
		|| (waveformat.fmtchunk.WaveFormatType != 1)) {

		GetWinMgr()->MessageBoxA("�t�@�C���̓ǂݍ��݂̎��s");
		return;
	}

	//data�`�����N
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

		//datachunk�X�V
		for (int i = 0; i < 4; i++)
		{
			waveformat.datachunk.datachunkID[i] = chunk_ID_temp[i];
		}
		waveformat.datachunk.chunkSize = chunksize_temp;

	}

	fclose(fp);

}
