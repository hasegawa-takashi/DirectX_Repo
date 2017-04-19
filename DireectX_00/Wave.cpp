#include "Wave.h"



CWave::CWave()
{
	header = { 0 };
}


CWave::~CWave()
{
}

void CWave::printHeader()
{
	std::cout << "[[HEADER]]" << std::endl;
	std::cout << "" << std::endl;

	std::cout << "[RIFF WAVE]" << std::endl;
	std::cout << "Chunk ID          : " << (char)header.chunkID[0]
		<< (char)header.chunkID[1]
		<< (char)header.chunkID[2]
		<< (char)header.chunkID[3] << std::endl;
	std::cout << "Size - 8          : " << header.size_8 << " Byte" << std::endl;
	std::cout << "Wave ID           : " << (char)header.waveID[0]
		<< (char)header.waveID[1]
		<< (char)header.waveID[2]
		<< (char)header.waveID[3] << std::endl;
	std::cout << "" << std::endl;

	std::cout << "[FMT CHUNK]" << std::endl;
	std::cout << "Chunk ID          : " << (char)header.fmt.chunkID[0]
		<< (char)header.fmt.chunkID[1]
		<< (char)header.fmt.chunkID[2]
		<< (char)header.fmt.chunkID[3] << std::endl;
	std::cout << "Chunk Size        : " << header.fmt.chunksize << " Byte" << std::endl;
	std::cout << "Format ID         : " << header.fmt.format_ID << std::endl;
	std::cout << "Channels          : " << header.fmt.Channel << std::endl;
	std::cout << "Sampling rate     : " << header.fmt.samplingrate << " Hz" << std::endl;
	std::cout << "Byte per second   : " << header.fmt.bytepersec << " B/s" << std::endl;
	std::cout << "Block size        : " << header.fmt.blocksize << " Byte" << std::endl;
	std::cout << "Bit depth         : " << header.fmt.bit_depth << " bit" << std::endl;
	std::cout << "" << std::endl;

	std::cout << "[DATA CHUNK]" << std::endl;
	std::cout << "Chunk ID          : " << (char)header.data.chunkID[0]
		<< (char)header.data.chunkID[1]
		<< (char)header.data.chunkID[2]
		<< (char)header.data.chunkID[3] << std::endl;
	std::cout << "Data size         : " << header.data.datasize << " Byte" << std::endl;
	std::cout << "" << std::endl;

	return;
}

int32_t CWave::datalength()
{
	return header.data.datasize / header.fmt.blocksize;
}

double CWave::lengthSec()
{
	return (double)header.data.datasize / header.fmt.bytepersec;
}



