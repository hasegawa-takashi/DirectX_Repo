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
//		XAudio2�̏�����
//
bool CSoundMgr::CreateXAudio()
{

	UINT32 flags = 0;
	m_pMasterVoice = NULL;


	if (FAILED(hr = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
	{
		return false;
	}

	// XAudio�̏�����
	if (FAILED(hr = XAudio2Create(&m_pXAudio, flags)))
	{
		return false;
	}


	// �g�p�\�I�[�f�B�I�f�o�C�X��
	m_pXAudio->GetDeviceCount(&m_devicecnt);

	// �f�o�C�X�̑I��
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

	// �}�X�^�[�{�C�X�̍쐬
	if (FAILED(hr = m_pXAudio->CreateMasteringVoice(&m_pMasterVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, preferredDevice, NULL)))
	{
		return false;
	}

	m_pXAudio->StartEngine();

}

////////////////////////////////////////////////////////////////
//
//	SouceVoice�ւ̓o�^
//
void CSoundMgr::SetSourcevoice(IXAudio2SourceVoice* m_Voice,WAVEFORMATEX waveformat)
{
	m_pXAudio->CreateSourceVoice(&m_Voice, &waveformat, 0);
}


