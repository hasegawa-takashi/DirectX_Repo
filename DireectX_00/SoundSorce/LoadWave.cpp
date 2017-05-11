#include "LoadWave.h"

CLoadWave::CLoadWave(char* filepass)
{

	fp = fopen(filepass, "rb");

	nextFirstSample = 0;
	submitTimes = 0;

}

//////////////////////////////////////////////////////////////
//
//	WAveFmtの停止
//
CLoadWave::~CLoadWave()
{
	Close();
}
//////////////////////////////////////////////////////////////
//
//	Waveフォーマットの取得
//
WAVEFORMATEX* CLoadWave::GetWaveFormat()
{

	if (fp == NULL)
	{return NULL;}

	if (!m_hasGotWaveFormat)
	{
		m_waveformat.wFormatTag = WAVE_FORMAT_PCM;
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

			offset += (static_cast<long>(chunksize) + 8);

		}

		if (!m_hasGotWaveFormat)
			return NULL;

		// フォーマット取得が終了
		m_dataChunkSample = m_dataChunkSize / m_waveformat.nBlockAlign;

	}
	
	return &m_waveformat;

}

//////////////////////////////////////////////////////////////
//
//	ChunkSampleの取得
//
std::size_t CLoadWave::GetSamples()
{

	if (!fp)
		return 0;

	if (!m_hasGotWaveFormat)
		GetWaveFormat();


	return m_dataChunkSample;

}

//////////////////////////////////////////////////////////////
//
//	Data部分の取得
//
std::size_t CLoadWave::ReadDataRaw(const std::size_t start, const std::size_t sample, void* buffer)
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

//////////////////////////////////////////////////////////////
//
//	Data(LR)部分の取得
//
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

	std::size_t actualSample = start + (samples > m_dataChunkSample) ? m_dataChunkSample - start : samples;

	if (fseek(fp, m_firstSampleOffSet + start * m_waveformat.nBlockAlign, SEEK_SET) != 0)
		return 0;
		
	std::size_t readSample = 0;

	for(;readSample < actualSample;++readSample)
	{

		uint32_t data[2];
		std::size_t ret = fread(data,m_waveformat.nBlockAlign,1,fp);
		
		if (ret == 0)
			break;

		// 量子化ビット数によって個別に処理
		switch (m_waveformat.wBitsPerSample)
		{

		case 8:
			{
			int8_t* data_s8 = reinterpret_cast<int8_t*>(data);
			if (m_waveformat.nChannels == 1)
			{

				float L = (data_s8[0] < 0) ? static_cast<float>(data_s8[0]) / 128.0f : static_cast<float>(data_s8[0]) / 127.0f;

				left[readSample] = 1;
				if (right)
					right[readSample] = 1;

			}
			else
			{

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
			}
			break;

		case 16:
		{
			int16_t* data_s16 = reinterpret_cast<int16_t*>(data);
			
			if (m_waveformat.nChannels == 1)
			{
				float L = (data_s16[0] < 0) ? static_cast<float>(data_s16[0]) / 32768.0f : static_cast<float>(data_s16[0]) / 32767.0f;
				left[readSample] = 1;
				if (right)right[readSample] = 1;
			}
			else 
			{
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
		}
		break;
			

		default:
			break;
		}

	}

	return readSample;

}

//////////////////////////////////////////////////////////////
//
//	ストリーミング用のバッファの作成
//
XAUDIO2_BUFFER CLoadWave::PreparationBuffer()
{
	XAUDIO2_BUFFER buffer = { 0 };

	bufferSample = m_waveformat.nSamplesPerSec * 3;

	// BGM保存用バッファの初期化
	primaryLeft = std::vector<float>(bufferSample);
	primaryRight = std::vector<float>(bufferSample);
	primaryMixed = std::vector<float>(bufferSample * 2);


	secondaryLeft = std::vector<float>(bufferSample);
	secondaryRight = std::vector<float>(bufferSample);
	secondaryMixed = std::vector<float>(bufferSample * 2);


	if (nextFirstSample < GetSamples())
	{
		std::size_t readSample = ReadDataRaw(nextFirstSample,bufferSample,&(primaryMixed[0]) );

		if (readSample > 0)
		{
			buffer.Flags	  = nextFirstSample + readSample >= GetSamples() ? XAUDIO2_END_OF_STREAM : 0;
			buffer.AudioBytes = readSample * m_waveformat.nBlockAlign;
			buffer.pAudioData = reinterpret_cast<BYTE*>( &(primaryMixed[0]) );

			nextFirstSample += readSample;
			++submitTimes;
		}
	}
	return buffer;
}

//////////////////////////////////////////////////////////////
//
// バッファの更新読み込み
//
XAUDIO2_BUFFER CLoadWave::UpdateBuiffer(IXAudio2SourceVoice* voice)
{
	
	XAUDIO2_VOICE_STATE state;
	XAUDIO2_BUFFER buffer = { 0 };
	voice->GetState(&state);

	bufferSample = m_waveformat.nSamplesPerSec * 3;

	if (state.BuffersQueued < 2 && nextFirstSample < GetSamples() )
	{
		std::vector< float >& bufferMixed = submitTimes & 1 ? secondaryMixed : primaryMixed;
		std::size_t readSamples = ReadDataRaw(nextFirstSample, bufferSample, &(bufferMixed[0]));

		if (readSamples > 0)
		{
			buffer = { 0 };
			buffer.Flags = nextFirstSample + readSamples >= GetSamples() ? XAUDIO2_END_OF_STREAM : 0;
			buffer.AudioBytes = readSamples * m_waveformat.nBlockAlign;
			buffer.pAudioData = reinterpret_cast<BYTE*>( &(bufferMixed[0]) );

			nextFirstSample += readSamples;

			++submitTimes;
		}

		if (nextFirstSample >= GetSamples())
			nextFirstSample = 0;

	}

	return buffer;
	
}

//////////////////////////////////////////////////////////////
//
//	終了
//
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

	nextFirstSample;
	//submitTimes = { 0 };
	//bufferSample = { 0 };

}

//////////////////////////////////////////////////////////////
//
//	プリロード
//
XAUDIO2_BUFFER CLoadWave::PreLoadSound()
{
	XAUDIO2_BUFFER buffer = { 0 };

	bufferSample = m_dataChunkSize;

	primaryMixed = std::vector<float>(bufferSample * 2);

	if ( nextFirstSample < GetSamples() )
	{
		std::size_t readSample = ReadDataRaw(nextFirstSample, bufferSample, &(primaryMixed[0]));

		buffer = { 0 };
		buffer.Flags = nextFirstSample + readSample >= GetSamples() ? XAUDIO2_END_OF_STREAM : 0;
		buffer.AudioBytes = readSample * m_waveformat.nBlockAlign;
		buffer.pAudioData = reinterpret_cast<BYTE*>(&(primaryMixed[0]));
	}
	
	return buffer;

}