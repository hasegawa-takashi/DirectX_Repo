#include "WaveDataOperater.h"



CWaveDataOperater::CWaveDataOperater()
{
}


CWaveDataOperater::~CWaveDataOperater()
{
}

/////////////////////////////////////////////////////////
//
//	Wave�t�@�C���̓ǂݍ���
//
void CWaveDataOperater::monoWaveRead(MONO_PCM *pcm, char *filename)
{
	FILE *fp;
	WAVE_FORMAT waveformat;

	fp = fopen(filename,"rb");

	if (!fp)
	{
		// ���s����
		// MesseageBox�ł�ok
		return;
	}

	//Riffdhunk�̓ǂݍ���
	fread(waveformat.riffchunk.chunkID,1,4,fp);
	fread(&waveformat.riffchunk.chunksize, 4, 1, fp);
	fread(waveformat.riffchunk.FormType, 1, 4, fp);

	//Formatchunk�̓ǂݍ���
	fread(waveformat.fmtchunk.chunkID,1,4,fp);
	fread(&waveformat.fmtchunk.chunksize, 4, 1, fp);
	fread(&waveformat.fmtchunk.WaveFormType, 2, 1, fp);
	fread(&waveformat.fmtchunk.Channel, 2, 1, fp);
	fread(&waveformat.fmtchunk.samplesPersec, 4, 1, fp);
	fread(&waveformat.fmtchunk.BytesPerSec, 4, 1, fp);
	fread(&waveformat.fmtchunk.BlockSize, 2, 1, fp);
	fread(&waveformat.fmtchunk.BitsPerSample, 2, 1, fp);

	// ���f�[�^�̓ǂݍ���
	fread(waveformat.datachunk.datachunkID,1,4,fp);
	fread(&waveformat.datachunk.chunkSize, 4, 1, fp);

	pcm->fs = waveformat.fmtchunk.samplesPersec;
	pcm->bits = waveformat.fmtchunk.BitsPerSample;
	pcm->length = waveformat.datachunk.chunkSize;
	pcm->sounddata = new double(pcm->length);



	// datachunk�̓ǂݍ���
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
//	Wave�t�@�C���̏����o��
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
	waveformat.fmtchunk.WaveFormType = 1;	// PCM�̏ꍇ��1
	waveformat.fmtchunk.Channel = 2;		// �X�e���I2 ���m����1
	waveformat.fmtchunk.samplesPersec = pcm->fs;
	waveformat.fmtchunk.BytesPerSec = (pcm->fs*pcm->bits)/8;
	waveformat.fmtchunk.BlockSize = pcm->bits / 8;
	waveformat.fmtchunk.BitsPerSample = pcm->bits;

	strcpy(waveformat.datachunk.datachunkID,"data");
	waveformat.datachunk.chunkSize = pcm->length * 2;

	fp = fopen(filename,"wb");

	if (!fp)
	{
		// �����~�X
	}


	fwrite(waveformat.fmtchunk.chunkID,1,4,fp);

	//Riffdhunk�̓ǂݍ���
	fwrite(waveformat.riffchunk.chunkID, 1, 4, fp);
	fwrite(&waveformat.riffchunk.chunksize, 4, 1, fp);
	fwrite(waveformat.riffchunk.FormType, 1, 4, fp);

	//Formatchunk�̓ǂݍ���
	fwrite(waveformat.fmtchunk.chunkID, 1, 4, fp);
	fwrite(&waveformat.fmtchunk.chunksize, 4, 1, fp);
	fwrite(&waveformat.fmtchunk.WaveFormType, 2, 1, fp);
	fwrite(&waveformat.fmtchunk.Channel, 2, 1, fp);
	fwrite(&waveformat.fmtchunk.samplesPersec, 4, 1, fp);
	fwrite(&waveformat.fmtchunk.BytesPerSec, 4, 1, fp);
	fwrite(&waveformat.fmtchunk.BlockSize, 2, 1, fp);
	fwrite(&waveformat.fmtchunk.BitsPerSample, 2, 1, fp);

	// ���f�[�^�̓ǂݍ���
	fwrite(waveformat.datachunk.datachunkID, 1, 4, fp);
	fwrite(&waveformat.datachunk.chunkSize, 4, 1, fp);

	pcm->fs = waveformat.fmtchunk.samplesPersec;
	pcm->bits = waveformat.fmtchunk.BitsPerSample;
	pcm->length = waveformat.datachunk.chunkSize;
	pcm->sounddata = new double(pcm->length);



	// datachunk�̓ǂݍ���
	short data;
	for (int loop = 0; loop < pcm->length; loop++)
	{
		fwrite(&data, 2, 1, fp);
		pcm->sounddata[loop] = (double)data / GROUND;
	}


	fclose(fp);

}