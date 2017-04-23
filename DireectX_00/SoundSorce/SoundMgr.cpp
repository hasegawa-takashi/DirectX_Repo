#include "SoundMgr.h"



CSoundMgr::CSoundMgr()
{
	//m_XAudiointerface = new CXAudio2Interface();


	HRESULT hr;
	m_XAudio2 = NULL;

	if (FAILED(hr = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
	{
		std::cout << "作成に失敗しました" << std::endl;
		return ;
	}

	if (FAILED(hr = XAudio2Create(&m_XAudio2, flags)))
	{
		std::cout << "XAudio2の作成失敗" << std::endl;
		CoUninitialize();
		return ;
	}

	// 使用可能オーディオデバイス数
	m_XAudio2->GetDeviceCount(&m_devicecnt);

	// デバイスの選択
	XAUDIO2_DEVICE_DETAILS devicedetails;
	int preferredDevice = 0;

	for (UINT loop = 0; loop < m_devicecnt; loop++)
	{
		m_XAudio2->GetDeviceDetails(loop, &devicedetails);
		if (devicedetails.OutputFormat.Format.nChannels > 2)
		{
			preferredDevice = loop;
		}
	}


	// マスターボイスの作成
	if (FAILED(hr = m_XAudio2->CreateMasteringVoice(&m_MasterVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, preferredDevice, NULL)))
	{
		std::cout << "マスターボイス作成失敗" << std::endl;
		CoUninitialize();
		return;
	}

}


CSoundMgr::~CSoundMgr()
{
}

void CSoundMgr::Init()
{
	m_Bgmdata = new CBgmDatabase();
}

void CSoundMgr::Play(bgmdata::BgmNameList name)
{

	m_Bgmdata->Play(name);

}

void CSoundMgr::Update()
{
	m_Bgmdata->Update();
}

bool CSoundMgr::SetXAudio2Souce(IXAudio2SourceVoice* s,const WAVEFORMATEX w)
{
	HRESULT hr;

	if (FAILED(hr = m_XAudio2->CreateSourceVoice(&s, &w)))
	{
		return false;
	}

	return true;
}