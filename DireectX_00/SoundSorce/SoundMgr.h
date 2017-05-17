#pragma once

#include"XAudio2Interface.h"
#include"BgmDatabase.h"
#include"SEDatabase.h"

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
	void SetReverbEffect(bgmdata::BgmNameList, float walltype, float roomsize);
	void SetEchoEffect(bgmdata::BgmNameList, float Delay, float feedback, float wetdry);
	void OffBGMReverb();
	void OffBGMEcho();

	// Se—p
	void Play(sedata::SeNameList, bool fadein);
	void Stop(sedata::SeNameList, bool fadeout);
	void SeVolume(float vol);
	void SetPitctlate(sedata::SeNameList, float late);
	void SetReverbEffect(sedata::SeNameList, float walltype,float roomsize);
	void SetEchoEffect(sedata::SeNameList, float Delay, float feedback, float wetdry);
	void OffSEReverb();
	void OffSEEcho();

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