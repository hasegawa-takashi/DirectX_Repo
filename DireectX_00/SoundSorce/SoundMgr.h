#pragma once

#include"BgmDatabase.h"
#include"XAudio2Interface.h"

class CSoundMgr
{
public:
	~CSoundMgr();

	static CSoundMgr* Instance(void){
		static CSoundMgr _instance;
		return &_instance;
	}
	
	void Play(bgmdata::BgmNameList);

	void Init();
	void Update();

	bool SetXAudio2Souce(IXAudio2SourceVoice**, const WAVEFORMATEX);

private:
	CSoundMgr();

	//CXAudio2Interface* m_XAudiointerface;
	CBgmDatabase* m_Bgmdata;


	IXAudio2* m_XAudio2;								// engine
	IXAudio2MasteringVoice* m_MasterVoice;				// MasterVoice

	UINT32 flags = 0;

	UINT32 m_devicecnt;
};

inline CSoundMgr* GetSoundMgr()
{
	return CSoundMgr::Instance();
}