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

	void Update();

	bool SetXAudio2Souce(IXAudio2SourceVoice**, WAVEFORMATEX*);

private:
	CSoundMgr();

	CXAudio2Interface* m_XAudiointerface;
	CBgmDatabase* m_Bgmdata;



};

inline CSoundMgr* GetSoundMgr()
{
	return CSoundMgr::Instance();
}