#pragma once

#include"../../Sound.h"
#include"../SoundComponent/SoundComponent.h"
#include"../../AudioDatabase/AudioDatabase.h"
#include"../../XAudio2/X3DAudio/X3DSound/X3DSound.h"

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
	void FadePlay(int FadeSpd);
	// ��~����
	void Stop();
	void FadeStop(int FadeSpd);
	// ���ʏ���
	void ChangeVolume( float volume );
	float GetVolume();

	bool EndSoundflag();

	// FFT�Ōv�Z�������ʂ̎擾
	bool GetSpectrumData();
	bool PlayNowFlag() { return m_PlayNowFlag; }
	void CalcFreq( size_t len, int Fs);
	float m_freqMagnitude[MAX_FREQ];

private:
	
	VoiceCallback* m_VoiceCallback;

	AudioElement* m_VoiceElement;	// ���̃R���|�[�l���g���ŕێ����Ă���T�E���h(���̂̓R�R)
									
	XAUDIO2_BUFFER m_Buffer;			// XAudio2�o�b�t�@�̐ݒ�

	std::vector<float> m_Spectrumdatas;

	bool m_PlayNowFlag;

	std::size_t m_StartSamplePoint;
	std::size_t m_EndSamplePoint;

	float m_Fadenum;		// ���݂�Fade�l
	int m_FadeSpd;

	void FadeInPlay();
	void FadeOutStop();
	std::function< void(void) > m_Fadefunc;
};