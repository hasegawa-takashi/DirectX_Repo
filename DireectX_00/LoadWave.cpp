#include "LoadWave.h"
#include<vector>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

CLoadWave::CLoadWave()
{
	fp = nullptr;
	has_file = false;
}

CLoadWave::CLoadWave(const char* filepath)
{
	fp = nullptr;
	has_file = false;
	header = { 0 };
	Openfile(filepath);
}

CLoadWave::~CLoadWave()
{
	Closefile();
}

bool CLoadWave::Openfile(const char* filepath)
{
	fp = fopen(filepath, "rb");

	if ( fp == NULL )
	{
		std::cerr << "ファイルパスが違う" << std::endl;
		has_file = false;
		return false;
	}

	// ヘッダー部分の読み取り
	fread(&header,sizeof(waveHeader),1,fp);
	data_beg = _ftelli64(fp);

	//形式チェック
	if (	(memcmp(&header.chunkID, "RIFF", 4) != 0) 
		||  (memcmp(&header.waveID, "WAVE", 4) != 0) 
		||  ( header.fmt.format_ID != 1) )
	{
		std::cerr << "不完全な形式です" << std::endl;
		has_file = false;
		Closefile();
		return false;
	}

	// datachunkの捜索
	if (memcmp(&header.data.chunkID, "data", 4) != 0)
	{
		uint8_t chunkID_tmp[4];
		uint32_t chunksize_tmp;

		//先頭からtiff+fmt分
		_fseeki64(fp,12+8+header.fmt.chunksize,SEEK_SET);

		fread(chunkID_tmp,1,4,fp);
		while (memcmp(chunkID_tmp,"data",4) != 0)
		{
			fread(&chunksize_tmp,4,1,fp);
			_fseeki64(fp, chunksize_tmp,SEEK_CUR);
			fread(chunkID_tmp, 1, 4, fp);
		}
		fread(&chunksize_tmp, 4, 1, fp);
		data_beg = _ftelli64(fp);

		//datachunkの更新
		for (int loop = 0; loop < 4; loop++)
		{
			header.data.chunkID[loop] = chunkID_tmp[loop ];
		}
		header.data.datasize = chunksize_tmp * header.fmt.Channel;
	}



	//先頭からtiff+fmt+dataまで
	//std::vector< BYTE > data(header.data.datasize);
	BYTE* data = new BYTE(header.data.datasize);
	_fseeki64(fp, 12 + 8 + header.fmt.chunksize + 8, SEEK_SET);

	/*for (int loop = 0 ; loop < header.data.datasize ; loop++)
	{
		fread(&data[loop], header.data.datasize, 1, fp);
	}*/

	fread(data,1,header.data.datasize,fp);

	has_file = true;


	fclose(fp);
	fp = nullptr;

	return true;

}

void CLoadWave::Closefile()
{
	header = { 0 };
	has_file = false;
}

void CLoadWave::getdata(uint8_t* data)
{
	getdatabuffer(data,0, datalength());
}
void CLoadWave::getdata(int16_t* data)
{
	getdatabuffer(data, 0, datalength());
}

void CLoadWave::getdata(uint8_t* L_data, uint8_t* R_data)
{
	getdatabuffer(L_data, R_data, 0, datalength());
}

void CLoadWave::getdata(int16_t* L_data, int16_t* R_data)
{
	getdatabuffer(L_data, R_data, 0, datalength());
}

void CLoadWave::getdatabuffer(uint8_t* data, uint32_t head, uint32_t datalength)
{
	_fseeki64(fp,data_beg+head ,SEEK_SET);

	if (header.fmt.Channel == 1) {
		fread(data,1,datalength,fp);
	}
	else
	{
		uint8_t* data_temp = new uint8_t[datalength*2];
		fread(data_temp , 1 , datalength*2,fp);
		for (uint32_t i = 0; i < datalength; i++)
		{
			data[i] = (uint8_t)(((uint16_t)data_temp[2 * i] + (uint16_t)data_temp[2 * i + 1]) / 2);
		}
		delete[] data_temp;
	}

}

void CLoadWave::getdatabuffer(int16_t* data, uint32_t head, uint32_t datalength)
{
	_fseeki64(fp, data_beg + head, SEEK_SET);

	if (header.fmt.Channel == 1) {
		fread(data, 2, datalength, fp);
	}
	else
	{
		uint16_t* data_temp = new uint16_t[datalength * 2];
		fread(data_temp, 2, datalength * 2, fp);
		for (uint32_t i = 0; i < datalength; i++)
		{
			data[i] = (uint16_t)(((uint32_t)data_temp[2 * i] + (uint32_t)data_temp[2 * i + 1]) / 2);
		}
		delete[] data_temp;
	}

}


void CLoadWave::getdatabuffer(uint8_t* L_data, uint8_t* R_data, uint32_t head, uint32_t datalength)
{
	_fseeki64(fp, data_beg + head, SEEK_SET);

	if (header.fmt.Channel == 1) {

		if (L_data != nullptr)
			fread(L_data, 1, datalength, fp);
		if (R_data != nullptr)
			fread(R_data, 1, datalength, fp);
	}
	else
	{
		uint8_t* data_temp = new uint8_t[datalength * 2];
		fread(data_temp, 1, datalength * 2, fp);

		if (L_data != nullptr)
		{
			for (uint32_t i = 0; i < datalength; i++)
			{
				L_data[i] = data_temp[i * 2];
			}
		}

			
		if (R_data != nullptr)
		{
			for (uint32_t i = 0; i < datalength; i++)
			{
				R_data[i] = data_temp[i * 2+1];
			}
		}

		delete[] data_temp;
	}
}

void CLoadWave::getdatabuffer(int16_t* L_data, int16_t* R_data, uint32_t head, uint32_t datalength)
{
	_fseeki64(fp, data_beg + head, SEEK_SET);

	if (header.fmt.Channel == 1) {

		if (L_data != nullptr)
			fread(L_data, 2, datalength, fp);
		if (R_data != nullptr)
			fread(R_data, 2, datalength, fp);
	}
	else
	{
		uint16_t* data_temp = new uint16_t[datalength * 2];
		fread(data_temp, 1, datalength * 2, fp);

		if (L_data != nullptr)
		{
			for (uint32_t i = 0; i < datalength; i++)
			{
				L_data[i] = data_temp[i * 2];
			}
		}


		if (R_data != nullptr)
		{
			for (uint32_t i = 0; i < datalength; i++)
			{
				R_data[i] = data_temp[i * 2 + 1];
			}
		}

		delete[] data_temp;
	}
}
