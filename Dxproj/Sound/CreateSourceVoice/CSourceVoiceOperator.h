#pragma once
#include"../Sound.h"
#include"../AudioDatabase/AudioDataBase.h"

#include"../XAudio2/X3DAudio/X3DSound/X3DSound.h"
#include"../XAudio2/XAPOFXEffect/VoiceEffect.h"
#include"../XAudio2/XAudio2Interface/XAudioInterface.h"
#include"../WaveformatData/WaveformatData.h"

/*
	Resourcesの情報郡
	サウンド再生に必要な情報はここに集まっています。
*/
struct VoiceElement
{
	SoundElement			Wavedata;		// 読み込みファイル情報
	IXAudio2SourceVoice*	Sourcevoice;	// Sourceボイス本体
	CVoiceEffect*			Effect;			// XAPOFXエフェクト	
	int						IdentNumb;		// ボイスの固有番号
	std::function<void()>   Soundfunc;		// 同期エフェクト用
};

/*
	サウンドのSourceボイスまわりの設定+処理をやる
*/
class CSourceVoiceOperator
{
public:
	CSourceVoiceOperator();
	~CSourceVoiceOperator();

	// ソースボイスの設定、作成
	int RegistVoice(SoundElement element);

	// 再生
	void VoicePlay(int identnumb);
	void VoicePlay(int identnumb,float fadespd);
	// 停止
	void VoiceStop(int identnumb);
	void VoiceStop(int identnumb,float fadespd);
	
	void Update();

	
	// エフェクトの設定
	void ChangeReverb(int identnumb,float walltype,float roomsize);
	void ChangeEcho(int identnumb, float Delay, float feedback, float wetdry);
	void ChangePitch(int identnumb, float PitchRate);
	// エフェクトのoff
	void OffReverb(int identnumb);
	void OffEcho(int identnumb);
	void OffPitch(int identnumb);

private:
	void FadeIn(float fadespd, VoiceElement* sourcevoice);
	void FadeOut(float fadespd, VoiceElement* sourcevoice);

	std::vector<VoiceElement*> m_Voicelist;	// 現在再生中のlist
	int m_Identity;							// 割り振り用変数
	float m_MasterVolume;					// このVoiceのくくりのマスターボリューム
};