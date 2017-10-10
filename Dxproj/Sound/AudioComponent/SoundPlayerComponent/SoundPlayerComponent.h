#pragma once

#include"../../Sound.h"
#include"../SoundComponent/SoundComponent.h"
#include"../../AudioDatabase/AudioDatabase.h"
#include"../../XAudio2/X3DAudio/X3DSound/X3DSound.h"
#include"../../XAudio2/XAPOFXEffect/VoiceEffect.h"

/*
*	CSoundPlayerComponent
*		�T�E���h��炷���߂ɕK���K�v��Component
*		�����o�^���Ȃ��Ƃ��߂Ȃ̂����ACSoundComponent�̃R���X�g���N�^�͎g���Ȃ��̂ł����ɋL��
*/

class CSoundPlayerComponent : public CSoundComponent
{
public:
	CSoundPlayerComponent();
	~CSoundPlayerComponent();

	// ������
	IXAudio2SourceVoice** Init(std::string Type, std::string Name);

	// �X�V����
	void ComponentUpdate();

	// �Đ�����
	void Play();

	// ��~����
	void Stop();

	// ���ʏ���
	void ChangeVolume( float volume );

	// FFT�Ōv�Z�������ʂ̎擾
	bool GetSpectrumData();

	bool PlayNowFlag() { return m_PlayNowFlag; }

	void CalcFreq( size_t len, int Fs);

	float m_freqMagnitude[MAX_FREQ];
private:
	
	AudioElement* m_VoiceElement;	// ���̃R���|�[�l���g���ŕێ����Ă���T�E���h(���̂̓R�R)
	CVoiceEffect* m_VoiceEffect;	// �G�t�F�N�g�̍쐬
	
	std::vector<float> m_Spectrumdatas;

	bool m_PlayNowFlag;

};

