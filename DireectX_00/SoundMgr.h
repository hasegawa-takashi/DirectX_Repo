#pragma once

#include<XAudio2.h>
#include"LoadWave.h"

class CSoundMgr
{
public:
	CSoundMgr();
	~CSoundMgr();


	void SetSourcevoice(IXAudio2SourceVoice*,WAVEFORMATEX);

	static CSoundMgr* Instance() {
		static CSoundMgr _Instance;
		return &_Instance;
	}



private:

	bool CreateXAudio();
	

	
private: // 変数
	IXAudio2* m_pXAudio;
	HRESULT hr;
	IXAudio2MasteringVoice* m_pMasterVoice;
	UINT32 m_devicecnt;
};


//=============================================================================
// デバイス呼び出し用
//=============================================================================
inline CSoundMgr* GetSoundMgr()
{
	return CSoundMgr::Instance();
}


