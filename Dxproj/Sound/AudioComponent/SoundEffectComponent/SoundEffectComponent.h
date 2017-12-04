#pragma once

class CSoundComponent;
#include"..\..\Sound.h"
#include "..\SoundComponent\SoundComponent.h"

#include<XAPOFX.h>
#pragma comment(lib,"XAPOFX.lib")
/*
*	
*	�T�E���h���ɕt������T�E���h�G�t�F�N�g
*	Cue�S�̂ɂ͔g�y���Ȃ��̂Œ���
*
*/
class CSoundEffectComponent : public CSoundComponent
{
public:
	CSoundEffectComponent();
	~CSoundEffectComponent();

	void Init(IXAudio2SourceVoice* voice);

	// �X�V����
	void ComponentUpdate() override;

	// ���o�[�u�p
	void SetReverbVolume(float walltype, float roomsize);
	void offsetReverbVolume();

	// �G�R�[�p
	void SetEchoVolume(float Delay, float feedback, float wetdry);
	void offsetEchoVolume();

	// �s�b�`���[�g�p
	void SetPitchRate(float PitchRate);
	void offsetPitchRate();

	// EQ�C�R���C�U�[�p
	void SetEQVolume(float freqcenter[4], float gain[4], float bandwidth[4]);
	void offSetEQVolume();

	// �F����ԗp
	void SetSpaceEffect();
	void offsetSpaceEffect();

	// �g���l����ԗp
	void SetTunnelEffect();
	void offsetTunnelEffect();

private:

	IXAudio2SourceVoice* m_voice;		// �o�^�����{�C�X�G�t�F�N�g
	IUnknown* m_Effect[3];

	XAUDIO2_EFFECT_CHAIN m_chain;
	XAUDIO2_EFFECT_DESCRIPTOR m_desc[3];

	FXREVERB_PARAMETERS m_Reverbpram;	// ���o�[�u�G�t�F�N�g
	FXECHO_PARAMETERS m_EchoPram;		// �G�R�[�G�t�F�N�g
	FXEQ_PARAMETERS m_EqPram;			// �C�R���C�U

	const int XAPOFX_EFFECT_TYPE = 3;	// XAPOFX�p�̒�`

	std::function< void() > Soundfunc;	// voice��func

	//
	float m_SpaceDlay = 1.6f;
	float m_SpaceFeedback = 0.3f;
	float m_SpaceDlywet = 0.3f;

	// �g���l�����P
	float m_TunnelWall = 0.2f;
	float m_TunnelRoomsize = 0.9f;
};

