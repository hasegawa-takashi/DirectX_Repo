#include "LoadOgg.h"

CLoadOgg::CLoadOgg(std::string soundlistnumb, bool Loopflag)
{
	m_SoundResouce.DataChunkSample = NULL;
	m_SoundResouce.DataChunkSize = NULL;
	m_SoundResouce.firstSampleOffSet = NULL;
	m_SoundResouce.HasGotWaveFormat = false;
	m_SoundResouce.Waveformat = {};
	m_SoundResouce.LoopSound = Loopflag;
	//m_PresetSoundName = soundlistnumb.c_str();
	m_TotalReadSize = 0;
	m_PresetSoundName = new char[soundlistnumb.size() + 1];
	std::strcpy(m_PresetSoundName, soundlistnumb.c_str());
	m_Playbuf = new char[BUFF_SIZE];
	m_Secondbuf = new char[BUFF_SIZE];
	LoadFormat();
}


CLoadOgg::~CLoadOgg()
{
	ov_clear(&m_Ovf);
	delete[] m_Playbuf;
	delete[] m_Secondbuf;
	delete[] m_PresetSoundName;
}

void CLoadOgg::LoadFormat()
{
	// oggfile���J��
	if (ov_fopen(m_PresetSoundName, &m_Ovf))
	{
		// �I�[�v�����s
		return;
	}

	// oggvorbisfile�����擾
	vorbis_info* vi = ov_info(&m_Ovf, -1);

	m_SoundResouce.Waveformat.wFormatTag = WAVE_FORMAT_PCM;
	m_SoundResouce.Waveformat.nChannels = vi->channels;
	m_SoundResouce.Waveformat.nSamplesPerSec = vi->rate;
	m_SoundResouce.Waveformat.nBlockAlign = vi->channels * 2;
	m_SoundResouce.Waveformat.wBitsPerSample = 16;
	m_SoundResouce.Waveformat.nAvgBytesPerSec = (vi->rate) * (vi->channels * 2);
	m_SoundResouce.Waveformat.cbSize = 0;

	
}

void CLoadOgg::Close()
{

}

XAUDIO2_BUFFER CLoadOgg::PreloadBuffer(std::size_t first, std::size_t last)
{

	XAUDIO2_BUFFER buffer = { 0 };

	

	return buffer;

}

std::vector<float> CLoadOgg::GetPrimaryBuffer()
{
	return primaryMixed;
}


XAUDIO2_BUFFER CLoadOgg::StreamloadBuffer()
{
	XAUDIO2_BUFFER buffer = { 0 };
	// oggfile���J��
	

	// oggvorbisfile�����擾
	vorbis_info* vi = ov_info(&m_Ovf, -1);

	buffer.AudioBytes = ReadDataRaw(0, 0, m_Playbuf);
	buffer.pAudioData = reinterpret_cast<BYTE*>(m_Playbuf);

	m_SoundResouce.SubmitTimes = 1;
	return buffer;
}

/// <summary>
/// �w��T�C�Y�ł̃o�b�t�@�̎擾
/// </summary>
/// <param name="start"></param>
/// <param name="sample"></param>
/// <param name="buffer"></param>
/// <returns></returns>
std::size_t CLoadOgg::ReadDataRaw(const std::size_t start, const std::size_t sample, char* buffer)
{
	if (buffer == 0)
	{
		return 0;
	}

	memset(buffer,0,BUFF_SIZE);
	int requestsize = BUFF_SIZE;
	int bitstream = 0;
	int readsize = 0;
	unsigned int comsize = 0;
	bool isadjust = false;

	if (BUFF_SIZE < requestsize)
	{
		requestsize = BUFF_SIZE;
		isadjust = true;
	}

	int cnt = 0;

	//�ǂݍ��݊J�n
	while (1)
	{
		// ogg�t�@�C���̓ǂݍ���
		readsize = ov_read(&m_Ovf, (char*)(buffer+comsize) , requestsize , 0 , 2 , 1 , &bitstream );
		
		comsize += readsize;

		if (readsize == 0)
		{
			// �t�@�C���G���h
			if (m_SoundResouce.LoopSound == true)
			{
				// ���ɖ߂�
				ov_time_seek(&m_Ovf, 0.0f);
			}
			else
			{
				// �ǂݍ��ݏI��
				return comsize;
			}
		}

		if (comsize >= BUFF_SIZE)
		{
			return comsize;
		}

		if (BUFF_SIZE - comsize < BUFF_SIZE)
		{
			isadjust = true;
			requestsize = BUFF_SIZE - comsize;
		}

	}

	// �G���[
	return 0;
}

/// <summary>
/// �o�b�t�@�̃A�b�v�f�[�g
/// </summary>
/// <param name="start"></param>
/// <param name="sample"></param>
/// <param name="buffer"></param>
/// <returns></returns>
XAUDIO2_BUFFER CLoadOgg::UpdateBuffer(IXAudio2SourceVoice* voice)
{
	XAUDIO2_VOICE_STATE state;
	XAUDIO2_BUFFER buffer = { 0 };

	// oggfile���J��
	voice->GetState(&state);

	// oggvorbisfile�����擾
	vorbis_info* vi = ov_info(&m_Ovf, -1);
	
	if (state.BuffersQueued < 2)
	{
		if (m_SoundResouce.SubmitTimes == 0)
		{
			int readsample = ReadDataRaw(0, 0, m_Playbuf);
			if (readsample > 0)
			{
				buffer.Flags = 0;
				buffer.AudioBytes = readsample;
				buffer.pAudioData = reinterpret_cast<BYTE*>(m_Playbuf);
				m_SoundResouce.SubmitTimes = 1;
			}
		}
		else if (m_SoundResouce.SubmitTimes == 1)
		{
			int readsample = ReadDataRaw(0, 0, m_Secondbuf);
			if (readsample > 0)
			{
				buffer.Flags = 0;
				buffer.AudioBytes = readsample;
				buffer.pAudioData = reinterpret_cast<BYTE*>(m_Secondbuf);
				m_SoundResouce.SubmitTimes = 0;
			}
		}
	}
	
	return buffer;

}