#pragma once

#include"../../Sound.h"
// TODO :: ƒtƒ@ƒCƒ‹ŠK‘w‚ª‚¨‚©‚µ‚¢
#include"../../../XAudio2DLLSet.h"



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
	bool ReleaseXAudio();
	bool SetXAudio2SourceVoice(IXAudio2SourceVoice**, const WAVEFORMATEX, VoiceCallback* voiceCallback);
	void SetMasterVolume(float Volume);

	float GetMasterVolume();
	IXAudio2* GetXAudioDevice() { return m_XAudio2; }
	IXAudio2MasteringVoice* GertXAudioMasterVoice() { return m_MasterVoice; }
	XAUDIO2_DEVICE_DETAILS GetDeviceDetails() { return devicedetails; }

private:
	CXAudioInterface();

	Xaudio2DllUnloadWorkaround_LoadLibraryVersion* m_Xaudio2dll;
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

