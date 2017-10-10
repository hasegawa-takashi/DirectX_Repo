#pragma once

#include"../Sound.h"
#include"../WaveformatData/WaveformatData.h"
#include"../XAudio2/XAudio2Interface/XAudioInterface.h"
#include"../SoundCue/SoundCue.h"

/*
*
* CAudioDatabase	
*	Component���Ő������ꂽ�f�[�^���Ǘ�/�ۑ�����ׂ̃X�N���v�g
*	singletonobject
*
*/
class CAudioDatabase
{
public:

	static CAudioDatabase* Instance()
	{
		static CAudioDatabase _Instance;
		return &_Instance;
	}

	~CAudioDatabase();

	// ����������
	void LoadResourceFile(std::string name);
	// ���ʑ���
	void ChangeCueVolume(std::string name,float volume);
	// �I������
	void CloseResourceFile();
	// Listener�̐ݒ�
	void SetListener(D3DXMATRIX* listener);
	// �f�[�^�̐ݒ�
	void SetAudioSource(AudioElement** audioelement, std::string type, std::string name);
	// �ۑ����Ă���f�[�^�̍폜
	void DeleteSoundData();

private:
	CAudioDatabase();

	std::map<std::string,CWaveformatData*> m_Waveformat;	// Waveformat�̏��̎擾
	std::map<std::string, CSoundCue*> m_Cuemap;				// ��� + SourceVoice

};