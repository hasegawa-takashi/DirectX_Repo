#pragma once

#include"../Sound.h"
#include"../FileLoad/LoadSoundFile.h"
#include"../FileLoad/Wave/LoadWave.h"

// WAVEFORMATEX��Csv�t�@�C������쐬�{�ۑ�������B
class CWaveformatData
{
public:
	CWaveformatData(std::string filepath);
	~CWaveformatData();

	SoundElement GetWaveElement(int listnumb);
	SoundElement GetWaveElement(std::string filepath);
	
	void RegistWaveformat(std::string filepath);

private:
	const char* m_cAudioPath = "../data/Sound/";	// �T�E���h�̃t�@�C���p�X
	std::vector<SoundElement> m_Formatlist;			// Wave�t�@�C���t�H�[�}�b�g

};