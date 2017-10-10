#pragma once

#include"../Sound.h"
#include"../WaveformatData/WaveformatData.h"
#include"../XAudio2/XAudio2Interface/XAudioInterface.h"
#include"../SoundCue/SoundCue.h"

/*
*
* CAudioDatabase	
*	Component内で生成されたデータを管理/保存する為のスクリプト
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

	// 初期化処理
	void LoadResourceFile(std::string name);
	// 音量操作
	void ChangeCueVolume(std::string name,float volume);
	// 終了処理
	void CloseResourceFile();
	// Listenerの設定
	void SetListener(D3DXMATRIX* listener);
	// データの設定
	void SetAudioSource(AudioElement** audioelement, std::string type, std::string name);
	// 保存しているデータの削除
	void DeleteSoundData();

private:
	CAudioDatabase();

	std::map<std::string,CWaveformatData*> m_Waveformat;	// Waveformatの情報の取得
	std::map<std::string, CSoundCue*> m_Cuemap;				// 種類 + SourceVoice

};