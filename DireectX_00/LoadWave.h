#pragma once
#include "Wave.h"
#include<cstdio>
#include<cstring>

#include<XAudio2.h>


class CLoadWave :
	public CWave
{
public:
	CLoadWave();
	CLoadWave(const char* fliepath);
	~CLoadWave();

	// ���m�����f�[�^
	void getdata(uint8_t* data);//���m����
	void getdata(int16_t* data);//�X�e���I

	// �X�e���I�f�[�^
	void getdata(uint8_t* L_data, uint8_t* R_data);//���m����
	void getdata(int16_t* L_data, int16_t* R_data);//�X�e���I

	bool gethasfile() { return has_file; }

	void GetWaveFileData(WAVEFORMATEX &file);

private:

	void getdatabuffer(uint8_t* data , uint32_t head , uint32_t datalength);
	void getdatabuffer(int16_t* data, uint32_t head, uint32_t datalength);

	void getdatabuffer(uint8_t* L_data, uint8_t* R_data, uint32_t head, uint32_t datalength);
	void getdatabuffer(int16_t* L_data, int16_t* R_data, uint32_t head, uint32_t datalength);

	bool has_file;
	bool Openfile(const char* fliepath);
	void Closefile();

	FILE* fp;
	uint32_t data_beg;
};

