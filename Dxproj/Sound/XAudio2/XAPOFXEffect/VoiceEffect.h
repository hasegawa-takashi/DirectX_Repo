#pragma once

#include"../../Sound.h"

#include<XAPOFX.h>

#pragma comment(lib,"XAPOFX.lib")

class CVoiceEffect
{
public:
	CVoiceEffect(IXAudio2SourceVoice* voice);
	~CVoiceEffect();

	// リバーブ用
	void SetReverbVolume(float walltype, float roomsize);
	void offsetReverbVolume();

	// エコー用
	void SetEchoVolume(float Delay, float feedback, float wetdry);
	void offsetEchoVolume();

	// ピッチレート用
	void SetPitchRate(float PitchRate);
	void offsetPitchRate();

private:
	IXAudio2SourceVoice* m_voice;
	IUnknown* m_Effect[3];

	XAUDIO2_EFFECT_CHAIN m_chain;
	XAUDIO2_EFFECT_DESCRIPTOR m_desc[3];

	FXREVERB_PARAMETERS m_Reverbpram;	// リバーブエフェクト
	FXECHO_PARAMETERS m_EchoPram;		// エコーエフェクト
	FXEQ_PARAMETERS m_EqPram;			// イコライザ(まだ何に使うんだ)

	const int XAPOFX_EFFECT_TYPE = 3;	// XAPOFX用の定義

	std::function< void() > Soundfunc;	// voiceのfunc

};

