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

	if (FAILED(hr = XAudio2Create(&m_XAudio2, m_flags)))
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

	/*

	// 3DSoundの初期化
	DWORD channelMask = devicedetails.OutputFormat.dwChannelMask;
	X3DAudioInitialize(channelMask,X3DAUDIO_SPEED_OF_SOUND, m_X3DInstance);

	// DSPSetteingの設定
	m_X3DDsp = { 0 };
	FLOAT32* matrix = new FLOAT32[devicedetails.OutputFormat.Format.nChannels];
	m_X3DDsp.SrcChannelCount = 1;
	m_X3DDsp.DstChannelCount = devicedetails.OutputFormat.Format.nChannels;
	m_X3DDsp.pMatrixCoefficients = matrix;
	delete matrix;
	
	*/

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
	m_MasterVolume = Volume;
	m_MasterVoice->SetVolume(m_MasterVolume);
}

/////////////////////////////////////////////////////////////////
//
//	全体音量の取得
//
float CXAudio2Interface::GetMasterVolume()
{
	m_MasterVolume = 0.0f;
	m_MasterVoice->GetVolume(&m_MasterVolume);
	return m_MasterVolume;
}

/////////////////////////////////////////////////////////////////
//
//	FadeOut
//
void CXAudio2Interface::MasterVoiceFadeOut()
{
	float NowVolume = 0.0f;
	m_MasterVoice->GetVolume(&NowVolume);
	
	if (NowVolume <= 0)
	{
		m_Fade = false;
		m_MasterVoice->SetVolume(0.0f);
	}
	NowVolume -= MasterVoiceData::FadeSpd;
	m_MasterVoice->SetVolume(NowVolume);
}

/////////////////////////////////////////////////////////////////
//
//	FadeIn
//
void CXAudio2Interface::MasterVoiceFadeIn()
{
	float NowVolume = 0.0f;
	m_MasterVoice->GetVolume(&NowVolume);

	if (NowVolume >= m_MasterVolume)
	{
		m_Fade = false;
		m_MasterVoice->SetVolume(m_MasterVolume);
	}
	NowVolume += MasterVoiceData::FadeSpd;
	m_MasterVoice->SetVolume(NowVolume);
}