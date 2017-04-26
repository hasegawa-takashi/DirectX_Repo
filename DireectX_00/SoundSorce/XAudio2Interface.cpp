#include "XAudio2Interface.h"



CXAudio2Interface::CXAudio2Interface()
{
	if ( !CreateXAudio() )
	{
		
	}

}


CXAudio2Interface::~CXAudio2Interface()
{
}

/////////////////////////////////////////////////////////////////
//
//	XAudioの作成
//
bool CXAudio2Interface::CreateXAudio()
{
	HRESULT hr;
	m_XAudio2 = NULL;

	if ( FAILED(hr = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
	{
		std::cout << "作成に失敗しました" << std::endl;
		return false;
	}

	if (FAILED(hr = XAudio2Create(&m_XAudio2, flags)))
	{
		std::cout << "XAudio2の作成失敗" << std::endl;
		CoUninitialize();
		return false;
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
		return false;
	}

	return true;
}

/////////////////////////////////////////////////////////////////
//
//	SouceVoiceの設定
//
bool CXAudio2Interface::SetXAudio2SouceVoice(IXAudio2SourceVoice** souce, WAVEFORMATEX wave)
{
	HRESULT hr;
	if (FAILED(hr = m_XAudio2->CreateSourceVoice(souce, &wave,0)))
	{
		return false;
	}
	return true;
}

/////////////////////////////////////////////////////////////////
//
//	全体音量の設定
//
void CXAudio2Interface::SetMasterVolume(float Volume)
{
	m_MasterVoice->SetVolume(Volume);
}

/////////////////////////////////////////////////////////////////
//
//	全体音量の取得
//
float CXAudio2Interface::GetMasterVolume()
{

	float vol = 0.0f;
	m_MasterVoice->GetVolume(&vol);
	return vol;
}