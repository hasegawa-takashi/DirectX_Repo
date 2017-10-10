#include "XAudioInterface.h"



CXAudioInterface::CXAudioInterface()
{
	CreateXAudio();
}


CXAudioInterface::~CXAudioInterface()
{
}

bool CXAudioInterface::CreateXAudio()
{
	HRESULT hr;
	m_XAudio2 = NULL;

	if (FAILED(hr = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
	{
		std::cout << "作成に失敗しました" << std::endl;
		return false;
	}

	if (FAILED(hr = XAudio2Create(&m_XAudio2, m_Flags)))
	{
		std::cout << "XAudio2の作成失敗" << std::endl;
		CoUninitialize();
		return false;
	}

	// 使用可能オーディオデバイス数
	m_XAudio2->GetDeviceCount(&m_DeviceCnt);

	// デバイスの選択
	int preferredDevice = 0;

	m_XAudio2->GetDeviceDetails(0, &devicedetails);

	if (devicedetails.OutputFormat.Format.nChannels > 8)
	{
		return false;
	}
	
	// マスターボイスの作成
	if (FAILED(hr = m_XAudio2->CreateMasteringVoice(&m_MasterVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, preferredDevice, NULL)))
	{
		std::cout << "マスターボイス作成失敗" << std::endl;
		CoUninitialize();
		return false;
	}

	return true;
}

bool CXAudioInterface::SetXAudio2SourceVoice(IXAudio2SourceVoice** souce, const WAVEFORMATEX wave)
{
	HRESULT hr;
	if (FAILED(hr = m_XAudio2->CreateSourceVoice(souce, &wave, 0)))
	{
		return false;
	}
	return true;
}

void CXAudioInterface::SetMasterVolume(float Volume)
{
	m_MasterVolume = Volume;
	m_MasterVoice->SetVolume(m_MasterVolume);
}

float CXAudioInterface::GetMasterVolume()
{
	m_MasterVolume = 0.0f;
	m_MasterVoice->GetVolume(&m_MasterVolume);
	return m_MasterVolume;
}