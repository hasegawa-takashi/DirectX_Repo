#include "SoundMgr.h"



CSoundMgr::CSoundMgr()
{
	//m_XAudiointerface = new CXAudio2Interface();


	HRESULT hr;
	m_XAudio2 = NULL;

	if (FAILED(hr = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
	{
		std::cout << "�쐬�Ɏ��s���܂���" << std::endl;
		return ;
	}

	if (FAILED(hr = XAudio2Create(&m_XAudio2, flags)))
	{
		std::cout << "XAudio2�̍쐬���s" << std::endl;
		CoUninitialize();
		return ;
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