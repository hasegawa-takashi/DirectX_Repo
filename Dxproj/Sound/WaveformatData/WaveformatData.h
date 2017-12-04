#pragma once

#include"../Sound.h"
#include"../FileLoad/LoadSoundFile.h"
#include"../FileLoad/Wave/LoadWave.h"
#include"../FileLoad/Ogg/LoadOgg.h"

// WAVEFORMATEXをCsvファイルから作成＋保存をする。
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
	
	const char* m_cAudioPath = "../data/Sound/";	// サウンドのファイルパス
	SoundElement m_Format;			// Waveファイルフォーマット

};