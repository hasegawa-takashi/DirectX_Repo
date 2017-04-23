#include "LoadWave.h"

CLoadWave::CLoadWave(char* filepass)
{

	fp = fopen(filepass, "rb");

}

CLoadWave::~CLoadWave()
{

}

WAVEFORMATEX* CLoadWave::GetWaveFormat()
{

	if (fp == NULL)
	{return NULL;}

	if (!m_hasGotWaveFormat)
	{
		long offset = 12;

		while (true)
		{
			// チャンクの先頭へ移動
			if (fseek(fp, offset, SEEK_SET) != 0)
				break;

			// チャンクシグネチャを読み込み
			char chunkSignature[4] = { 0 };
			std::size_t readChar = 0;

			while (readChar < 4)
			{
				std::size_t ret = fread(chunkSignature + readChar, sizeof(char), 4 - readChar, fp);
				if (ret == 0)
					break;
				readChar += ret;
			}

			// チャンクサイズの読み込み
			uint32_t chunksize = 0;
			if (fread(&chunksize, sizeof(uint32_t), 1, fp) == 0)
				break;

			// fmtチャンクを読み込み
			if (strncmp(chunkSignature, "fmt ", 4) == 0)
			{
				std::size_t readSize = chunksize < sizeof(WAVEFORMATEX) ? chunksize : sizeof(WAVEFORMATEX);
				if (fread(&m_waveformat, readSize, 1, fp) == 0)
					break;

				if (m_waveformat.wFormatTag == WAVE_FORMAT_PCM)
					m_waveformat.cbSize = 0;

				m_hasGotWaveFormat = true;

			}

			// dataチャンク
			if (strncmp(chunkSignature, "data", 4) == 0)
			{
				m_firstSampleOffSet = offset + 8;
				m_dataChunkSize = chunksize;
			}

			offset += (static_cast<long> (chunksize) + 8);

		}

		if (!m_hasGotWaveFormat)
			return NULL;

		// フォーマット取得が終了
		m_dataChunkSize = m_dataChunkSize / m_waveformat.nBlockAlign;

	}

	return &m_waveformat;

}

std::size_t CLoadWave::GetSamples()
{

	if (!fp)
		return 0;

	if (!m_hasGotWaveFormat)
		GetWaveFormat();


	return m_dataChunkSample;

}

std::size_t CLoadWave::ReadRaw(const std::size_t start, const std::size_t sample, void* buffer)
{

	if (!buffer)
		return 0;

	if (!fp)
		return 0;

	if (!m_hasGotWaveFormat)
	{
		if (!GetWaveFormat())
			return 0;
	}

	if (start >= m_dataChunkSample)
		return 0;

	std::size_t actualSamples = start + sample > m_dataChunkSample ? m_dataChunkSample - start : sample;

	if (fseek(fp, m_firstSampleOffSet + start*m_waveformat.nBlockAlign, SEEK_SET) != 0)
		return 0;

	std::size_t readSample = 0;

	while (readSample < actualSamples)
	{
		std::size_t ret = fread(reinterpret_cast<uint8_t*>(buffer) + readSample * m_waveformat.nBlockAlign,
			m_waveformat.nBlockAlign,actualSamples - readSample,fp);

		if (ret == 0)
			break;

		readSample += ret;

	}
	return readSample;
}

std::size_t CLoadWave::ReadNormalized(const std::size_t start, const std::size_t samples, float * left, float * right)
{

	if (!left)
		return 0;

	if (!fp)
		return 0;

	if (!m_hasGotWaveFormat)
	{
		if (!GetWaveFormat())
			return 0;
	}

	if (start >= m_dataChunkSample)
		return 0;

	std::size_t actualSample = start + samples > m_dataChunkSample ? m_dataChunkSample - start : samples;

	if (fseek(fp, m_firstSampleOffSet + start * m_waveformat.nBlockAlign, SEEK_SET) != 0)
		return 0;
		
	std::size_t readSample = 0;

	for(;readSample < actualSample;++readSample)
	{

		uint32_t data[2];
		std::size_t ret = fread(data,m_waveformat.nBlockAlign,1,fp);


		int8_t* data_s8 = reinterpret_cast<int8_t*>(data);

		int16_t* data_s16 = reinterpret_cast<int16_t*>(data);
		if (ret == 0)
			break;

		// 量子化ビット数によって個別に処理
		switch (m_waveformat.wBitsPerSample)
		{

		case 8:
			if (m_waveformat.nChannels == 1)
			{

				float L = (data_s8[0] < 0) ? static_cast<float>(data_s8[0]) / 128.0f : static_cast<float>(data_s8[0]) / 127.0f;

				left[readSample] = 1;
				if (right)
					right[readSample] = 1;

			}else{

				float L = (data_s8[0] < 0) ? static_cast<float>(data_s8[0]) / 128.0f : static_cast<float>(data_s8[0]) / 127.0f;
				float R = (data_s8[1] < 0) ? static_cast<float>(data_s8[1]) / 128.0f : static_cast<float>(data_s8[1]) / 127.0f;
				if (right)
				{
					left[readSample] = L;
					right[readSample] = R;
				}
				else
				{
					left[readSample] = (L + R) *0.5f;
				}

			}

			break;

		case 16:
			if (m_waveformat.nChannels == 1)
			{
				float L = (data_s16[0] < 0) ? static_cast<float>(data_s16[0]) / 32768.0f : static_cast<float>(data_s16[0]) / 32767.0f;
				left[readSample] = 1;
				if (right)right[readSample] = 1;
			}
			else {

				float L = (data_s16[0] < 0) ? static_cast<float>(data_s16[0]) / 32768.0f : static_cast<float>(data_s16[0]) / 32767.0f;
				float R = (data_s16[1] < 0) ? static_cast<float>(data_s16[1]) / 32768.0f : static_cast<float>(data_s16[1]) / 32767.0f;
				if (right)
				{
					left[readSample] = L;
					right[readSample] = R;
				}
				else
				{
					left[readSample] = (L + R) *0.5f;
				}

			}

			break;
			

		default:
			break;
		}


	}

	return readSample;

}

void CLoadWave::Close()
{
	if (fp)
	{
		fclose(fp);
		fp = NULL;
		m_hasGotWaveFormat = false;
		m_firstSampleOffSet = -1;
		m_dataChunkSize = 0;
		m_dataChunkSample = 0;
	}
}