#include "LoadWave.h"


//====================================
//
//	サウンドの設定とループの設定 + 初期化
//
//====================================
CLoadWave::CLoadWave( char* Soundlistnumb, bool Loopflag)
{
	m_SoundResouce.m_DataChunkSample = NULL;
	m_SoundResouce.m_DataChunkSize = NULL;
	m_SoundResouce.m_firstSampleOffSet = NULL;
	m_SoundResouce.m_HasGotWaveFormat = false;
	m_SoundResouce.m_Waveformat = {};
	m_SoundResouce.m_LoopSound = Loopflag;
	m_PresetSoundName = Soundlistnumb;

	LoadFormat();
}


CLoadWave::~CLoadWave()
{
}

//====================================
//
//	WAVEFORMATEXへのchunk情報の格納
//
//====================================
void CLoadWave::LoadFormat()
{

	FILE* fp;

	fp = fopen(m_PresetSoundName,"rb");

	if (fp == NULL)
		return;

	m_SoundResouce.m_Waveformat.wFormatTag = WAVE_FORMAT_PCM;
	long offset = 12;

	while (true)
	{

		if (fseek(fp, offset, SEEK_SET) != 0)
			break;

		char chunksignature[4] = { 0 };
		std::size_t readChar = 0;

		while (readChar < 4)
		{
			std::size_t ret = fread(chunksignature + readChar,sizeof(char),4-readChar,fp);
			if (ret == 0)
				break;
			readChar += ret;
		}

		uint32_t chunksize = 0;
		if (fread(&chunksize, sizeof(uint32_t), 1, fp) == 0)
			break;

		// fmtチャンクを読み込み
		if (strncmp(chunksignature, "fmt ", 4) == 0)
		{
			std::size_t readSize = chunksize < sizeof(WAVEFORMATEX) ? chunksize : sizeof(WAVEFORMATEX);
			if (fread(&m_SoundResouce.m_Waveformat, readSize, 1, fp) == 0)
				break;

			if (m_SoundResouce.m_Waveformat.wFormatTag == WAVE_FORMAT_PCM)
				m_SoundResouce.m_Waveformat.cbSize = 0;

			m_SoundResouce.m_HasGotWaveFormat = true;

		}

		// dataチャンク
		if (strncmp(chunksignature, "data", 4) == 0)
		{
			m_SoundResouce.m_firstSampleOffSet = offset + 8;
			m_SoundResouce.m_DataChunkSize = chunksize;
		}

		offset += (static_cast<long>(chunksize) + 8);

	}

	if (!m_SoundResouce.m_HasGotWaveFormat)
		return;

	// フォーマット取得が終了
	m_SoundResouce.m_DataChunkSample = m_SoundResouce.m_DataChunkSize / m_SoundResouce.m_Waveformat.nBlockAlign;

	fclose(fp);
}

//====================================
//
//	WAVEFORMATEXへのbuffer情報の格納
//
//====================================
XAUDIO2_BUFFER CLoadWave::PreloadBuffer()
{
	std::size_t nextFirstSample = { 0 };
	std::size_t bufferSample = { 0 };
	std::vector<float> primaryMixed = { 0 };

	XAUDIO2_BUFFER buffer = { 0 };

	bufferSample = m_SoundResouce.m_DataChunkSize;

	primaryMixed = std::vector<float>(bufferSample * 2);

	if (nextFirstSample < m_SoundResouce.m_DataChunkSample)
	{
		std::size_t readSample = ReadDataRaw(nextFirstSample, bufferSample, &(primaryMixed[0]));

		buffer = { 0 };
		buffer.Flags = nextFirstSample + readSample >= m_SoundResouce.m_DataChunkSample ? XAUDIO2_END_OF_STREAM : 0;
		buffer.AudioBytes = readSample * m_SoundResouce.m_Waveformat.nBlockAlign;
		buffer.pAudioData = reinterpret_cast<BYTE*>(&(primaryMixed[0]));
	}

	return buffer;
}

//====================================
//
//	WAVEFORMATEXへのbuffer情報の格納
//	stremingbuffer
//
//====================================
XAUDIO2_BUFFER CLoadWave::StreamloadBuffer()
{
	XAUDIO2_BUFFER buffer = { 0 };
	std::size_t bufferSample = { 0 };

	std::vector<float> primaryLeft = { 0 };
	std::vector<float> primaryRight = { 0 };
	
	std::vector< float > secondaryLeft = { 0 };
	std::vector< float > secondaryRight = { 0 };

	bufferSample = m_SoundResouce.m_Waveformat.nSamplesPerSec * 3;

	// BGM保存用バッファの初期化
	primaryLeft = std::vector<float>(bufferSample);
	primaryRight = std::vector<float>(bufferSample);
	primaryMixed = std::vector<float>(bufferSample * 2);


	secondaryLeft = std::vector<float>(bufferSample);
	secondaryRight = std::vector<float>(bufferSample);
	secondaryMixed = std::vector<float>(bufferSample * 2);

	if (m_SoundResouce.m_NextFirstSample < m_SoundResouce.m_DataChunkSample)
	{
		std::size_t readSample = ReadDataRaw(m_SoundResouce.m_NextFirstSample, bufferSample, &(primaryMixed[0]));

		if (readSample > 0)
		{
			buffer.Flags = m_SoundResouce.m_NextFirstSample + readSample >= m_SoundResouce.m_DataChunkSample ? XAUDIO2_END_OF_STREAM : 0;
			buffer.AudioBytes = readSample * m_SoundResouce.m_Waveformat.nBlockAlign;
			buffer.pAudioData = reinterpret_cast<BYTE*>(&(primaryMixed[0]));

			m_SoundResouce.m_NextFirstSample += readSample;
			++m_SoundResouce.m_SubmitTimes;
		}
	}
	return buffer;
}

//====================================
//
//	WAVEFORMATEXへのbuffer情報の更新
//	stremingbuffer	再生が修了すると -1 が返る
//
//====================================
XAUDIO2_BUFFER CLoadWave::UpdateBuiffer(IXAudio2SourceVoice* const voice)
{
	XAUDIO2_VOICE_STATE state;
	XAUDIO2_BUFFER buffer = { 0 };
	std::size_t bufferSample = { 0 };

	std::vector<float> primaryLeft = { 0 };
	std::vector<float> primaryRight = { 0 };

	std::vector< float > secondaryLeft = { 0 };
	std::vector< float > secondaryRight = { 0 };

	voice->GetState(&state);

	bufferSample = m_SoundResouce.m_Waveformat.nSamplesPerSec * 3;

	if (state.BuffersQueued < 2 && m_SoundResouce.m_NextFirstSample < m_SoundResouce.m_DataChunkSample)
	{
		std::vector< float >& bufferMixed = m_SoundResouce.m_SubmitTimes & 1 ? secondaryMixed : primaryMixed;
		std::size_t readSamples = ReadDataRaw(m_SoundResouce.m_NextFirstSample, bufferSample, &(bufferMixed[0]));

		if (readSamples > 0)
		{
			buffer = { 0 };
			buffer.Flags = m_SoundResouce.m_NextFirstSample + readSamples >= m_SoundResouce.m_DataChunkSample ? XAUDIO2_END_OF_STREAM : 0;
			buffer.AudioBytes = readSamples * m_SoundResouce.m_Waveformat.nBlockAlign;
			buffer.pAudioData = reinterpret_cast<BYTE*>(&(bufferMixed[0]));

			m_SoundResouce.m_NextFirstSample += readSamples;

			++m_SoundResouce.m_SubmitTimes;
		}

		if (m_SoundResouce.m_NextFirstSample >= m_SoundResouce.m_DataChunkSample&& m_SoundResouce.m_LoopSound == true)
				m_SoundResouce.m_NextFirstSample = 0;
		else
		{
			// 終了検知
			return buffer = { -1 };
		}

	}

	return buffer;
}

//////////////////////////////////////////////////////////////
//
//	PCM 16bit? Data部分の取得
//
///////////////////////////////////////////////////////////////
std::size_t CLoadWave::ReadDataRaw(const std::size_t start, const std::size_t sample, void* buffer)
{

	FILE* fp;

	fp = fopen(m_PresetSoundName, "rb");

	if (!buffer)
		return 0;

	if (!fp)
		return 0;

	if (!m_SoundResouce.m_HasGotWaveFormat)
		return 0;

	if (start >= m_SoundResouce.m_DataChunkSample)
		return 0;

	std::size_t actualSamples = start + sample > m_SoundResouce.m_DataChunkSample ? m_SoundResouce.m_DataChunkSample - start : sample;

	if (fseek(fp, m_SoundResouce.m_firstSampleOffSet + start * m_SoundResouce.m_Waveformat.nBlockAlign, SEEK_SET) != 0)
		return 0;

	std::size_t readSample = 0;

	while (readSample < actualSamples)
	{
		std::size_t ret = fread(reinterpret_cast<uint8_t*>(buffer) + readSample * m_SoundResouce.m_Waveformat.nBlockAlign,
			m_SoundResouce.m_Waveformat.nBlockAlign, actualSamples - readSample, fp);

		if (ret == 0)
			break;

		readSample += ret;
	}

	fclose(fp);

	return readSample;
}