#pragma once
#include"../Sound.h"
#include"../AudioDatabase/AudioDataBase.h"

#include"../XAudio2/X3DAudio/X3DSound/X3DSound.h"
#include"../XAudio2/XAPOFXEffect/VoiceEffect.h"
#include"../XAudio2/XAudio2Interface/XAudioInterface.h"
#include"../WaveformatData/WaveformatData.h"

/*
	Resources�̏��S
	�T�E���h�Đ��ɕK�v�ȏ��͂����ɏW�܂��Ă��܂��B
*/
struct VoiceElement
{
	SoundElement			Wavedata;		// �ǂݍ��݃t�@�C�����
	IXAudio2SourceVoice*	Sourcevoice;	// Source�{�C�X�{��
	CVoiceEffect*			Effect;			// XAPOFX�G�t�F�N�g	
	int						IdentNumb;		// �{�C�X�̌ŗL�ԍ�
	std::function<void()>   Soundfunc;		// �����G�t�F�N�g�p
};

/*
	�T�E���h��Source�{�C�X�܂��̐ݒ�+���������
*/
class CSourceVoiceOperator
{
public:
	CSourceVoiceOperator();
	~CSourceVoiceOperator();

	// �\�[�X�{�C�X�̐ݒ�A�쐬
	int RegistVoice(SoundElement element);

	// �Đ�
	void VoicePlay(int identnumb);
	void VoicePlay(int identnumb,float fadespd);
	// ��~
	void VoiceStop(int identnumb);
	void VoiceStop(int identnumb,float fadespd);
	
	void Update();

	
	// �G�t�F�N�g�̐ݒ�
	void ChangeReverb(int identnumb,float walltype,float roomsize);
	void ChangeEcho(int identnumb, float Delay, float feedback, float wetdry);
	void ChangePitch(int identnumb, float PitchRate);
	// �G�t�F�N�g��off
	void OffReverb(int identnumb);
	void OffEcho(int identnumb);
	void OffPitch(int identnumb);

private:
	void FadeIn(float fadespd, VoiceElement* sourcevoice);
	void FadeOut(float fadespd, VoiceElement* sourcevoice);

	std::vector<VoiceElement*> m_Voicelist;	// ���ݍĐ�����list
	int m_Identity;							// ����U��p�ϐ�
	float m_MasterVolume;					// ����Voice�̂�����̃}�X�^�[�{�����[��
};