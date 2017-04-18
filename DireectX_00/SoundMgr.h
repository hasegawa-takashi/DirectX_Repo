#pragma once

#include<XAudio2.h>
#include <mmsystem.h>

#include"LoadWave.h"

class CBGM;

class CSoundMgr
{
public:
	static CSoundMgr* Instance() {
	static CSoundMgr _Instance;
	return &_Instance;
	}

	void SetMasterVolume(float Vol);	// 全体音声の設定
	float GetMasterVolume();			// 全体音声の取得

	CSoundMgr();
	~CSoundMgr();



	void SetSourcevoice(IXAudio2SourceVoice**,WAVEFORMATEX*);

	void InitSoundMgr();

	void Play(int bgm);

private:

	bool CreateXAudio();
	

	
private: // 変数
	IXAudio2* m_pXAudio;
	HRESULT hr;
	IXAudio2MasteringVoice* m_pMasterVoice;
	UINT32 m_devicecnt;

	CBGM* m_BgmVoice;

};


//=============================================================================
// デバイス呼び出し用
//=============================================================================
inline CSoundMgr* GetSoundMgr()
{
	return CSoundMgr::Instance();
}


