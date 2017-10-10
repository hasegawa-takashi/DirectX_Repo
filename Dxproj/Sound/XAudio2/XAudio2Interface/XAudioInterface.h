#pragma once

#include"../../Sound.h"

class CXAudioInterface
{
public:

	static CXAudioInterface* Instance()
	{
		static CXAudioInterface _Instance;
		return &_Instance;
	}


	~CXAudioInterface();

	bool CreateXAudio();
	bool SetXAudio2SourceVoice(IXAudio2SourceVoice**, const WAVEFORMATEX);
	void SetMasterVolume(float Volume);

	float GetMasterVolume();
	IXAudio2* GetXAudioDevice() { return m_XAudio2; }
	IXAudio2MasteringVoice* GertXAudioMasterVoice() { return m_MasterVoice; }
	XAUDIO2_DEVICE_DETAILS GetDeviceDetails() { return devicedetails; }

private:
	CXAudioInterface();

	IXAudio2* m_XAudio2;
	IXAudio2MasteringVoice* m_MasterVoice;
	UINT32 m_Flags;
	UINT32 m_DeviceCnt;
	XAUDIO2_DEVICE_DETAILS devicedetails;
	float m_MasterVolume = 1;
};

inline CXAudioInterface* GetXAudio2Mgr()
{
	return CXAudioInterface::Instance();
}
