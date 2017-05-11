#pragma once

#include"BgmDatabase.h"
#include"SEDatabase.h"
#include"XAudio2Interface.h"

class CSoundMgr
{
public:
	~CSoundMgr();

	static CSoundMgr* Instance(void){
		static CSoundMgr _instance;
		return &_instance;
	}
	
	void Init();
	void Update();

	// BGM—p
	void Play(bgmdata::BgmNameList, bool fadein);
	void Stop(bgmdata::BgmNameList, bool fadeout);
	void BgmVolume(float vol);
	void SetPitctlate(bgmdata::BgmNameList, float late );

	// Se—p
	void Play(sedata::SeNameList);
	void Stop(sedata::SeNameList);
	void SeVolume(float vol);
	void SetPitctlate(sedata::SeNameList, float late);
	void SetReverbEffect(float walltype,float roomsize);

private:
	CSoundMgr();

	CBgmDatabase* m_Bgmdata;							// BgmList
	CSEDatabase* m_Sedata;


	UINT32 flags = 0;

	UINT32 m_devicecnt;
};

inline CSoundMgr* GetSoundMgr()
{
	return CSoundMgr::Instance();
}