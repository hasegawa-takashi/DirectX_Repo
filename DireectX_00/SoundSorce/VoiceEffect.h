#pragma once

#include<XAPOFX.h>
#include<XAudio2.h>
#include<functional>

#pragma comment(lib,"X3daudio.lib")
#pragma comment(lib,"XAPOFX.lib")

namespace effect_type {
	// エフェクトのタイプ
	enum EFFECT_TYPE {
		PITCHRATE = 0,
		REVERB,
		ECHO,
		EQUALIZER,
		MAX_EFFECT
	};
}

//------------------------------------------------------------
//
//	音のエフェクト用のクラス
//
//------------------------------------------------------------
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
	void PitchRate( float PitchRate);

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

