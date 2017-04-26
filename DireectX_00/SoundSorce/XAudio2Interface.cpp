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
//	XAudio�̍쐬
//
bool CXAudio2Interface::CreateXAudio()
{
	HRESULT hr;
	m_XAudio2 = NULL;

	if ( FAILED(hr = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
	{
		std::cout << "�쐬�Ɏ��s���܂���" << std::endl;
		return false;
	}

	if (FAILED(hr = XAudio2Create(&m_XAudio2, flags)))
	{
		std::cout << "XAudio2�̍쐬���s" << std::endl;
		CoUninitialize();
		return false;
	}

	// �g�p�\�I�[�f�B�I�f�o�C�X��
	m_XAudio2->GetDeviceCount(&m_devicecnt);

	// �f�o�C�X�̑I��
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


	// �}�X�^�[�{�C�X�̍쐬
	if (FAILED(hr = m_XAudio2->CreateMasteringVoice(&m_MasterVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, preferredDevice, NULL)))
	{
		std::cout << "�}�X�^�[�{�C�X�쐬���s" << std::endl;
		CoUninitialize();
		return false;
	}

	return true;
}

/////////////////////////////////////////////////////////////////
//
//	SouceVoice�̐ݒ�
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
//	�S�̉��ʂ̐ݒ�
//
void CXAudio2Interface::SetMasterVolume(float Volume)
{
	m_MasterVoice->SetVolume(Volume);
}

/////////////////////////////////////////////////////////////////
//
//	�S�̉��ʂ̎擾
//
float CXAudio2Interface::GetMasterVolume()
{

	float vol = 0.0f;
	m_MasterVoice->GetVolume(&vol);
	return vol;
}