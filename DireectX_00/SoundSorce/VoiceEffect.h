#pragma once

#include<XAPOFX.h>
#include<XAudio2.h>
#include<functional>

#pragma comment(lib,"X3daudio.lib")
#pragma comment(lib,"XAPOFX.lib")

namespace effect_type {
	// �G�t�F�N�g�̃^�C�v
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
//	���̃G�t�F�N�g�p�̃N���X
//
//------------------------------------------------------------
class CVoiceEffect
{
public:
	CVoiceEffect(IXAudio2SourceVoice* voice);
	~CVoiceEffect();
	
	// ���o�[�u�p
	void SetReverbVolume(float walltype, float roomsize);
	void offsetReverbVolume();
	
	// �G�R�[�p
	void SetEchoVolume(float Delay, float feedback, float wetdry);
	void offsetEchoVolume();
	
	// �s�b�`���[�g�p
	void PitchRate( float PitchRate);

private:
	IXAudio2SourceVoice* m_voice;
	IUnknown* m_Effect[3];

	XAUDIO2_EFFECT_CHAIN m_chain;
	XAUDIO2_EFFECT_DESCRIPTOR m_desc[3];

	FXREVERB_PARAMETERS m_Reverbpram;	// ���o�[�u�G�t�F�N�g
	FXECHO_PARAMETERS m_EchoPram;		// �G�R�[�G�t�F�N�g
	FXEQ_PARAMETERS m_EqPram;			// �C�R���C�U(�܂����Ɏg����)
	
	const int XAPOFX_EFFECT_TYPE = 3;	// XAPOFX�p�̒�`

	std::function< void() > Soundfunc;	// voice��func

};

