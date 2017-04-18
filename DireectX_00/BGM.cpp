#include "BGM.h"

//==========================================================
//
//		CBGM�n
//
//==========================================================
static const char* g_pszFileBGM[BGMList::MAX_BGM] = {
	"../data/Sound/Bgm/test.wav"
};

CBGM::CBGM()
{
	ReadWaveFile();
}

CBGM::~CBGM()
{
	Close();
};

//////////////////////////////////////////////////////////////
//
//	WaveFile��BGM�Ƃ��ēo�^
//
void CBGM::ReadWaveFile()
{

	CLoadWave *wave;
	WAVEFORMATEX wavefmt;
	XAUDIO2_BUFFER buffer = { 0 };

	for (int loop = 0; loop < BGMList::MAX_BGM; loop++)
	{
		wave = new CLoadWave(g_pszFileBGM[loop]);
		waveHeader header = wave->GetWaveDat();

		// WAVEFORMAT�̐ݒ�
		wavefmt.wFormatTag = WAVE_FORMAT_PCM;
		wavefmt.nChannels = header.fmt.Channel;
		wavefmt.nSamplesPerSec = header.fmt.samplingrate;
		wavefmt.nAvgBytesPerSec = wavefmt.nSamplesPerSec * wavefmt.nChannels / 8;
		wavefmt.wBitsPerSample = header.fmt.bit_depth;
		wavefmt.nBlockAlign = wavefmt.nChannels * wavefmt.wBitsPerSample / 8;
		wavefmt.cbSize = 0;

		// XAUDIO2_BUFFER�̐ݒ�
		rawdata = wave->GetRawData();
		buffer.AudioBytes = header.fmt.chunksize;
		buffer.pAudioData = rawdata;
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

		GetSoundMgr()->SetSourcevoice(&m_Voice[loop], &wavefmt);
		m_Voice[loop]->SubmitSourceBuffer(&buffer);
	}
}

//////////////////////////////////////////////////////////////
//	�Đ�
void CBGM::PlayBGM(int bgmlist)
{
	HRESULT hr =  m_Voice[bgmlist]->Start();

	if (FAILED(hr))
	{
		int i = 0;
	}
}

//////////////////////////////////////////////////////////////
//	BGM���ʂ̐ݒ�
void CBGM::SetBGMVol(float vol)
{
	for (int i = 0; i < BGMList::MAX_BGM; i++)
	{
		m_Voice[i]->SetVolume(vol);
	}

	Volume = vol;
}

//////////////////////////////////////////////////////////////
//	BGM���ʂ̎擾
float CBGM::GetBGMVol()
{
	return Volume;
}

//////////////////////////////////////////////////////////////
//	BGM�̌�n��
void CBGM::Close()
{
	for (int i = 0; i < BGMList::MAX_BGM; i++)
	{
		m_Voice[i]->DestroyVoice();
	}
}