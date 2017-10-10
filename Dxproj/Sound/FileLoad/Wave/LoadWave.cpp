#include "LoadWave.h"


//====================================
//
//	サウンドの設定とループの設定 + 初期化
//
//====================================
CLoadWave::CLoadWave(std::string Soundlistnumb, bool Loopflag)
{
	m_SoundResouce.DataChunkSample = NULL;
	m_SoundResouce.DataChunkSize = NULL;
	m_SoundResouce.firstSampleOffSet = NULL;
	m_SoundResouce.HasGotWaveFormat = false;
	m_SoundResouce.Waveformat = {};
	m_SoundResouce.LoopSound = Loopflag;

	//m_PresetSoundName = Soundlistnumb.c_str();

	m_PresetSoundName = new char[Soundlistnumb.size() + 1];
	std::strcpy( m_PresetSoundName , Soundlistnumb.c_str());

	LoadFormat();
}


CLoadWave::~CLoadWave()
{
	
	Close();

}


void CLoadWave::Close()
{
	delete[] m_PresetSoundName;
	secondaryMixed.clear();
}

//====================================
//
//	WAVEFORMATEXへのchunk情報の格納
//
//====================================
void CLoadWave::LoadFormat()
{

	FILE* fp;

	fopen_s(&fp, m_PresetSoundName, "rb");

	if (fp == NULL)
		return;

	m_SoundResouce.Waveformat.wFormatTag = WAVE_FORMAT_PCM;
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
			if (fread(&m_SoundResouce.Waveformat, readSize, 1, fp) == 0)
				break;

			if (m_SoundResouce.Waveformat.wFormatTag == WAVE_FORMAT_PCM)
				m_SoundResouce.Waveformat.cbSize = 0;

			m_SoundResouce.HasGotWaveFormat = true;

		}

		// dataチャンク
		if (strncmp(chunksignature, "data", 4) == 0)
		{
			m_SoundResouce.firstSampleOffSet = offset + 8;
			m_SoundResouce.DataChunkSize = chunksize;
		}

		offset += (static_cast<long>(chunksize) + 8);

	}

	if (!m_SoundResouce.HasGotWaveFormat)
		return;

	// フォーマット取得が終了
	m_SoundResouce.DataChunkSample = m_SoundResouce.DataChunkSize / m_SoundResouce.Waveformat.nBlockAlign;

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
	//std::vector<float> primaryMixed = { 0 };

	XAUDIO2_BUFFER buffer = { 0 };

	bufferSample = m_SoundResouce.DataChunkSize;

	primaryMixed = std::vector<float>(bufferSample * 2);

	if (nextFirstSample < m_SoundResouce.DataChunkSample)
	{
		std::size_t readSample = ReadDataRaw(nextFirstSample, bufferSample, &(primaryMixed[0]));

		buffer = { 0 };
		buffer.Flags = nextFirstSample + readSample >= m_SoundResouce.DataChunkSample ? XAUDIO2_END_OF_STREAM : 0;
		buffer.AudioBytes = readSample * m_SoundResouce.Waveformat.nBlockAlign;
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

	//bufferSample = m_SoundResouce.Waveformat.nSamplesPerSec * 2;
	bufferSample = BUFF_SIZE;

	// BGM保存用バッファの初期化
	primaryLeft = std::vector<float>(bufferSample);
	primaryRight = std::vector<float>(bufferSample);
	primaryMixed = std::vector<float>(bufferSample * 2);


	secondaryLeft = std::vector<float>(bufferSample);
	secondaryRight = std::vector<float>(bufferSample);
	secondaryMixed = std::vector<float>(bufferSample * 2);

	if (m_SoundResouce.NextFirstSample < m_SoundResouce.DataChunkSample)
	{
		std::size_t readSample = ReadDataRaw(m_SoundResouce.NextFirstSample, bufferSample, &(primaryMixed[0]));

		if (readSample > 0)
		{
			buffer.Flags = m_SoundResouce.NextFirstSample + readSample >= m_SoundResouce.DataChunkSample ? XAUDIO2_END_OF_STREAM : 0;
			buffer.AudioBytes = readSample * m_SoundResouce.Waveformat.nBlockAlign;
			buffer.pAudioData = reinterpret_cast<BYTE*>(&(primaryMixed[0]));

			m_SoundResouce.NextFirstSample += readSample;
			++m_SoundResouce.SubmitTimes;

			m_BufferLoadflag = true;
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
XAUDIO2_BUFFER CLoadWave::UpdateBuffer(IXAudio2SourceVoice* voice)
{
	XAUDIO2_VOICE_STATE state;
	XAUDIO2_BUFFER buffer = { 0 };
	std::size_t bufferSample = { 0 };

	std::vector<float> primaryLeft = { 0 };
	std::vector<float> primaryRight = { 0 };

	std::vector< float > secondaryLeft = { 0 };
	std::vector< float > secondaryRight = { 0 };

	voice->GetState(&state);

	//bufferSample = m_SoundResouce.Waveformat.nSamplesPerSec * 2;
	bufferSample = BUFF_SIZE;


	if (state.BuffersQueued < 2 && m_SoundResouce.NextFirstSample < m_SoundResouce.DataChunkSample)
	{
		std::vector< float >& bufferMixed = m_SoundResouce.SubmitTimes & 1 ? secondaryMixed : primaryMixed;
		std::size_t readSamples = ReadDataRaw(m_SoundResouce.NextFirstSample, bufferSample, &(bufferMixed[0]));

		if (readSamples > 0)
		{
			buffer = { 0 };
			buffer.Flags = m_SoundResouce.NextFirstSample + readSamples >= m_SoundResouce.DataChunkSample ? XAUDIO2_END_OF_STREAM : 0;
			buffer.AudioBytes = readSamples * m_SoundResouce.Waveformat.nBlockAlign;
			buffer.pAudioData = reinterpret_cast<BYTE*>(&(bufferMixed[0]));

			m_SoundResouce.NextFirstSample += readSamples;

			++m_SoundResouce.SubmitTimes;

			m_BufferLoadflag = true;

		}

		if (m_SoundResouce.NextFirstSample >= m_SoundResouce.DataChunkSample&& m_SoundResouce.LoopSound == true)
		{
			m_SoundResouce.NextFirstSample = 0;
		}
		else
		{
			// 終了検知
			return buffer;
		}

	}

	return buffer;
}

//////////////////////////////////////////////////////////////
//
//	PCM 16bit? Data部分の取得
//
///////////////////////////////////////////////////////////////
std::size_t CLoadWave::ReadDataRaw(std::size_t start, std::size_t sample, void* buffer)
{

	FILE* fp;

	fopen_s(&fp,m_PresetSoundName, "rb");

	if (!buffer)
		return 0;

	if (!fp)
		return 0;

	if (!m_SoundResouce.HasGotWaveFormat)
		return 0;

	if (start >= m_SoundResouce.DataChunkSample)
		return 0;

	std::size_t actualSamples = start + sample > m_SoundResouce.DataChunkSample ? m_SoundResouce.DataChunkSample - start : sample;

	if (fseek(fp, m_SoundResouce.firstSampleOffSet + start * m_SoundResouce.Waveformat.nBlockAlign, SEEK_SET) != 0)
		return 0;

	std::size_t readSample = 0;

	while (readSample < actualSamples)
	{
		std::size_t ret = fread(reinterpret_cast<uint8_t*>(buffer) + readSample * m_SoundResouce.Waveformat.nBlockAlign,
			m_SoundResouce.Waveformat.nBlockAlign, actualSamples - readSample, fp);

		if (ret == 0)
			break;

		readSample += ret;
	}

	fclose(fp);

	return readSample;
}

bool CLoadWave::GetNextbufferTime(IXAudio2SourceVoice* voice)
{
	if (m_BufferLoadflag)
	{
		m_BufferLoadflag = false;
		return true;
	}

	return false;

}

std::vector<float> CLoadWave::GetPrimaryBuffer()
{
	return primaryMixed;
}