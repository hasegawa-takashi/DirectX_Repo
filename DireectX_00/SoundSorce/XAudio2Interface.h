#pragma once

#include<XAudio2.h>
#include<X3DAudio.h>
#include<iostream>

#include"VoiceEffect.h"

#pragma comment(lib,"X3daudio.lib")

namespace MasterVoiceData {
	const float FadeSpd = 0.01f;
}

// 必要なもの
struct SoundData
{
	IXAudio2SourceVoice*	Voice;				// サウンド
	VoiceCallback			VoiceCallBack;		// コールバック
	CLoadWave*				SourceWaveFormat;	// waveファイルの色々
	CVoiceEffect			VoiceEffect;		// 各種エフェクト

	float Volume;								// 単体の音量
	bool  Loop;									// ループ再生するのか？
	bool  Fade;									// Fadeflag
};


/////////////////////////////////////////////////////////////////
//
//	XAudio2の準備等々
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

	// XAudio2エンジン
	IXAudio2* m_XAudio2;
	IXAudio2MasteringVoice* m_MasterVoice;
	
	// 3DSound用（未実装）
	X3DAUDIO_HANDLE m_X3DInstance;
	X3DAUDIO_DSP_SETTINGS m_X3DDsp;
	
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
//	XAudio2のCallBack
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
