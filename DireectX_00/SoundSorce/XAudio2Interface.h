#pragma once

#include<XAudio2.h>
#include<X3DAudio.h>
#include <iostream>

namespace MasterVoiceData {
	const float FadeSpd = 0.1f;
}

/////////////////////////////////////////////////////////////////
//
//	XAudio2ÇÃèÄîıìôÅX
//
class CXAudio2Interface
{
public:
	static CXAudio2Interface* Instance()
	{
		static CXAudio2Interface _Instance;
		return &_Instance;
	}

	~CXAudio2Interface();
	
	bool CreateXAudio();

	bool SetXAudio2SouceVoice(IXAudio2SourceVoice**, const WAVEFORMATEX);

	void SetMasterVolume(float Volume);
	float GetMasterVolume();
	
	void MasterVoiceFadeOut();
	void MasterVoiceFadeIn();

private:
	CXAudio2Interface();

	IXAudio2* m_XAudio2;
	IXAudio2MasteringVoice* m_MasterVoice;
	X3DAUDIO_HANDLE X3DInstance;

	UINT32 m_flags = 0;
	UINT32 m_devicecnt;

	float m_MasterVolume = 1;
	bool m_Fade = false;

};

inline CXAudio2Interface* GetXAudio2Mgr()
{
	return CXAudio2Interface::Instance();
}

/////////////////////////////////////////////////////////////////
//
//	XAudio2ÇÃCallBack
//
class VoiceCallback : public IXAudio2VoiceCallback
{
public:
	HANDLE hBufferEndEvent;
	VoiceCallback() : hBufferEndEvent(CreateEvent(NULL, FALSE, FALSE, NULL)) {}
	~VoiceCallback() { CloseHandle(hBufferEndEvent); }

	void _stdcall OnVoiceProcessingPassStart(UINT32 SamplesRequired) override {    }
	void _stdcall OnVoiceProcessingPassEnd() override { }
	void _stdcall OnStreamEnd() override { SetEvent(hBufferEndEvent); }
	void _stdcall OnBufferStart(void * pBufferContext) override {    }
	void _stdcall OnBufferEnd(void * pBufferContext) override { }
	void _stdcall OnLoopEnd(void * pBufferContext) override {    }
	void _stdcall OnVoiceError(void * pBufferContext, HRESULT Error) override { }
};
