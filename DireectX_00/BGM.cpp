#include "BGM.h"

//==========================================================
//
//		CBGM系
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
//	WaveFileをBGMとして登録
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

		// WAVEFORMATの設定
		wavefmt.wFormatTag = WAVE_FORMAT_PCM;
		wavefmt.nChannels = header.fmt.Channel;
		wavefmt.nSamplesPerSec = header.fmt.samplingrate;
		wavefmt.nAvgBytesPerSec = wavefmt.nSamplesPerSec * wavefmt.nChannels / 8;
		wavefmt.wBitsPerSample = header.fmt.bit_depth;
		wavefmt.nBlockAlign = wavefmt.nChannels * wavefmt.wBitsPerSample / 8;
		wavefmt.cbSize = 0;

		// XAUDIO2_BUFFERの設定
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
//	再生
void CBGM::PlayBGM(int bgmlist)
{
	HRESULT hr =  m_Voice[bgmlist]->Start();

	if (FAILED(hr))
	{
		int i = 0;
	}
}

//////////////////////////////////////////////////////////////
//	BGM音量の設定
void CBGM::SetBGMVol(float vol)
{
	for (int i = 0; i < BGMList::MAX_BGM; i++)
	{
		m_Voice[i]->SetVolume(vol);
	}

	Volume = vol;
}

//////////////////////////////////////////////////////////////
//	BGM音量の取得
float CBGM::GetBGMVol()
{
	return Volume;
}

//////////////////////////////////////////////////////////////
//	BGMの後始末
void CBGM::Close()
{
	for (int i = 0; i < BGMList::MAX_BGM; i++)
	{
		m_Voice[i]->DestroyVoice();
	}
}