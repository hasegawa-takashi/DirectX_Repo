#pragma once

#include"../../Sound.h"
#include"../SoundComponent/SoundComponent.h"
#include"../../AudioDatabase/AudioDatabase.h"
#include"../../XAudio2/X3DAudio/X3DSound/X3DSound.h"

/*
*	CSoundPlayerComponent
*		サウンドを鳴らすために必ず必要なComponent
*		これを登録しないとだめなのだが、CSoundComponentのコンストラクタは使えないのでここに記入
*/

class CSoundPlayerComponent : public CSoundComponent
{
public:
	CSoundPlayerComponent();
	~CSoundPlayerComponent();

	// 初期化
	IXAudio2SourceVoice** Init(std::string Type, std::string Name);

	// 更新処理
	void ComponentUpdate();

	// 再生処理
	void Play();
	void FadePlay(int FadeSpd);
	// 停止処理
	void Stop();
	void FadeStop(int FadeSpd);
	// 音量処理
	void ChangeVolume( float volume );
	float GetVolume();

	bool EndSoundflag();

	// FFTで計算した結果の取得
	bool GetSpectrumData();
	bool PlayNowFlag() { return m_PlayNowFlag; }
	void CalcFreq( size_t len, int Fs);
	float m_freqMagnitude[MAX_FREQ];

private:
	
	VoiceCallback* m_VoiceCallback;

	AudioElement* m_VoiceElement;	// このコンポーネント内で保持しているサウンド(実体はココ)
									
	XAUDIO2_BUFFER m_Buffer;			// XAudio2バッファの設定

	std::vector<float> m_Spectrumdatas;

	bool m_PlayNowFlag;

	std::size_t m_StartSamplePoint;
	std::size_t m_EndSamplePoint;

	float m_Fadenum;		// 現在のFade値
	int m_FadeSpd;

	void FadeInPlay();
	void FadeOutStop();
	std::function< void(void) > m_Fadefunc;
};