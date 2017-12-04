#pragma once

#include"../Sound.h"
#include"../FileLoad/LoadSoundFile.h"
#include"../FileLoad/Wave/LoadWave.h"
#include"../FileLoad/Ogg/LoadOgg.h"

// WAVEFORMATEX��Csv�t�@�C������쐬�{�ۑ�������B
class CWaveformatData
{
public:
	CWaveformatData(std::string filepath, std::string Soundname);
	~CWaveformatData();

	//SoundElement GetWaveElement(int listnumb);
	//SoundElement GetWaveElement(std::string filepath);
	SoundElement GetWaveElement();


private:
	void RegistWaveformat(std::string filepath,std::string Soundname);
	
	const char* m_cAudioPath = "../data/Sound/";	// �T�E���h�̃t�@�C���p�X
	SoundElement m_Format;			// Wave�t�@�C���t�H�[�}�b�g

};