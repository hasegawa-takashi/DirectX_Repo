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

	void Play(bgmdata::BgmNameList, bool fadein);
	void Stop(bgmdata::BgmNameList, bool fadeout);

	void Play(sedata::SeNameList);
	void Stop(sedata::SeNameList);

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