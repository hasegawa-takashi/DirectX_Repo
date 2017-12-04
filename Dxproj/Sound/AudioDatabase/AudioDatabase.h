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
	void SetVoiceCue(std::string name, AudioElement* voice);
	void PopVoiceCue(std::string name, AudioElement* voice);

	// 音量操作
	void ChangeCueVolume(std::string name,float volume);


	// Listenerの設定
	void SetListener(D3DXMATRIX* listener);
	// データの設定
	void SetAudioSource(AudioElement* audioelement, std::string type, std::string name, VoiceCallback* voiceCallback);

private:
	CAudioDatabase();
	// 保存しているデータの削除
	void DeleteSoundData();

	std::map<std::string, CSoundCue> m_Cuemap;				// 種類 + SourceVoice

};