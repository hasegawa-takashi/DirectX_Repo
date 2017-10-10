#pragma once

#include"../Sound.h"
#include"../FileLoad/LoadSoundFile.h"
#include"../FileLoad/Wave/LoadWave.h"

// WAVEFORMATEXをCsvファイルから作成＋保存をする。
class CWaveformatData
{
public:
	CWaveformatData(std::string filepath);
	~CWaveformatData();

	SoundElement GetWaveElement(int listnumb);
	SoundElement GetWaveElement(std::string filepath);
	
	void RegistWaveformat(std::string filepath);

private:
	const char* m_cAudioPath = "../data/Sound/";	// サウンドのファイルパス
	std::vector<SoundElement> m_Formatlist;			// Waveファイルフォーマット

};