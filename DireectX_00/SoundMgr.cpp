#include "SoundMgr.h"



CSoundMgr::CSoundMgr()
{
}


CSoundMgr::~CSoundMgr()
{
}

void CSoundMgr::InitSoundMgr()
{
	CreateXAudio();
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

void CSoundMgr::SetMasterVolume(float Vol )
{
	m_pMasterVoice->SetVolume(Vol);
}

float CSoundMgr::GetMasterVolume()
{
	float vol;
	m_pMasterVoice->GetVolume(&vol);
	return vol;
}

////////////////////////////////////////////////////////////////
//	SouceVoiceへの登録
void CSoundMgr::SetSourcevoice(IXAudio2SourceVoice** m_Voice,WAVEFORMATEX* waveformat)
{
	m_pXAudio->CreateSourceVoice(m_Voice, waveformat, 0);
}

////////////////////////////////////////////////////////////////
//	Bgmの再生
void CSoundMgr::Play(int bgm)
{
	m_BgmVoice->PlayBGM(bgm);
}