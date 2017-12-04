#pragma once
#include"../Sound.h"
#include"../XAudio2/X3DAudio/X3DSound/X3DSound.h"

/**
*
*	�T�E���h�t�@�C���̎�ގ���XAudioSourcevoice�z��
*	case ) BGM , SE , VOICE , UiSE �cetc
*
*/
class CSoundCue
{
public:
	CSoundCue();
	~CSoundCue();

	void Registervoice(AudioElement* voice);	// �V�K�{�C�X�̓o�^
	void ChangeVolume(float volume);			// ���ʂ̒���
	void UnRegistervoice(AudioElement* voice);	// �o�^�{�C�X�̍폜

private:
	std::vector< AudioElement* > m_Voicelist;	// �o�^����Ă���{�C�X
		
	bool m_CueMute;								// �~���[�g�t���O
	float m_CueVolume;							// Cue�ʃ{�����[��
};

