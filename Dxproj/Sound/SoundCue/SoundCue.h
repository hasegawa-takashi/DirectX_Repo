#pragma once
#include"../Sound.h"
#include"../XAudio2/X3DAudio/X3DSound/X3DSound.h"

/**
*
*	サウンドファイルの種類事のXAudioSourcevoice配列
*	case ) BGM , SE , VOICE , UiSE …etc
*
*/
class CSoundCue
{
public:
	CSoundCue();
	~CSoundCue();

	void Registervoice(AudioElement* voice);	// 新規ボイスの登録
	void ChangeVolume(float volume);			// 音量の調節
	void UnRegistervoice(AudioElement* voice);	// 登録ボイスの削除

private:
	std::vector< AudioElement* > m_Voicelist;	// 登録されているボイス

	//CVoiceEffect m_CueEffect;	/* 現在エフェクトが足りないので使わない */
	
	bool m_CueMute;								// ミュートフラグ
	float m_CueVolume;							// Cue別ボリューム
};

