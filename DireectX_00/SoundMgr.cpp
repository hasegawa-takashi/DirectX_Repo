#include "SoundMgr.h"



CSoundMgr::CSoundMgr()
{
	CreateXAudio();
}


CSoundMgr::~CSoundMgr()
{
}

//==========================================================
//
//		XAudio2の初期化
//
bool CSoundMgr::CreateXAudio()
{

	UINT32 flags = 0;
	m_pMasterVoice = NULL;


	if (FAILED(hr = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
	{
		return false;
	}

	// XAudioの初期化
	if (FAILED(hr = XAudio2Create(&m_pXAudio, flags)))
	{
		return false;
	}


	// 使用可能オーディオデバイス数
	m_pXAudio->GetDeviceCount(&m_devicecnt);

	// デバイスの選択
	XAUDIO2_DEVICE_DETAILS devicedetails;
	int preferredDevice = 0;

	for (UINT loop = 0;loop < m_devicecnt ; loop++)
	{
		m_pXAudio->GetDeviceDetails(loop, &devicedetails);
		if (devicedetails.OutputFormat.Format.nChannels > 2)
		{
			preferredDevice = loop;
		}
	}

	// マスターボイスの作成
	if (FAILED(hr = m_pXAudio->CreateMasteringVoice(&m_pMasterVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, preferredDevice, NULL)))
	{
		return false;
	}

	m_pXAudio->StartEngine();

}

//==========================================================
//
//		Waaveファイルの読み込み
//
void CSoundMgr::WaveFileLoad(const char filepath)
{
	wave = new CLoadWave(&filepath);
	waveHeader header = wave->GetWaveDat();

	wavefmt.wFormatTag = WAVE_FORMAT_PCM;
	wavefmt.nChannels = header.fmt.Channel;
	wavefmt.nSamplesPerSec = header.fmt.samplingrate;
	wavefmt.nAvgBytesPerSec = wavefmt.nSamplesPerSec * wavefmt.nChannels / 8;
	wavefmt.wBitsPerSample = header.fmt.bit_depth;
	wavefmt.nBlockAlign = wavefmt.nChannels * wavefmt.wBitsPerSample / 8;
	wavefmt.cbSize = 0;

	m_pXAudio->CreateSourceVoice(&Voice,&wavefmt,0);

}

