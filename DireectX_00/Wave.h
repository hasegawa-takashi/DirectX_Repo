#pragma once

#include <iostream>

/*
ここ見ました
http://arithmeticoverflow.blog.fc2.com/blog-entry-43.html
*/


typedef struct {
	uint8_t chunkID[4];
	uint32_t chunksize;
	uint16_t format_ID;
	uint16_t Channel;
	uint32_t samplingrate;
	uint32_t bytepersec;
	uint16_t blocksize;
	uint16_t bit_depth;
} fmtchunk;

typedef struct {
	uint8_t chunkID[4];
	uint32_t datasize;
} datachunk;

// riff含むwaveファイルのヘッダー部分
typedef struct {
	uint8_t chunkID[4];
	uint32_t size_8;
	uint8_t waveID[4];
	fmtchunk fmt;
	datachunk data;
} waveHeader;

class CWave
{
public:
	CWave();
	virtual ~CWave();

	void printHeader();
	int32_t datalength();
	double lengthSec();

protected:
	waveHeader header;
};

