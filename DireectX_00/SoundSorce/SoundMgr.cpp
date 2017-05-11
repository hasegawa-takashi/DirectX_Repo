#include "SoundMgr.h"



CSoundMgr::CSoundMgr()
{

}


CSoundMgr::~CSoundMgr()
{
	delete m_Bgmdata;
	delete m_Sedata;
}

///////////////////////////////////////////////////////////
//
//	初期化
//
void CSoundMgr::Init()
{
	m_Bgmdata = new CBgmDatabase();
	m_Sedata = new CSEDatabase();
}

///////////////////////////////////////////////////////////
//
//	再生
//
void CSoundMgr::Play(bgmdata::BgmNameList name, bool fadein)
{
	m_Bgmdata->Play(name,fadein);
}

///////////////////////////////////////////////////////////
//
//	停止
//
void CSoundMgr::Stop(bgmdata::BgmNameList name, bool fadeout)
{
	m_Bgmdata->Stop(name, fadeout);
}

///////////////////////////////////////////////////////////
//
//	BGMの音量
//
void CSoundMgr::BgmVolume(float vol)
{
	m_Bgmdata->SetBgmVolume(vol);
}

///////////////////////////////////////////////////////////
//
//	BGMのピッチレート
//
void CSoundMgr::SetPitctlate(bgmdata::BgmNameList numb, float late)
{
	m_Bgmdata->PitchRate(numb, late);
}

///////////////////////////////////////////////////////////
//
//	再生
//
void CSoundMgr::Play(sedata::SeNameList name)
{
	m_Sedata->Play(name);
}

///////////////////////////////////////////////////////////
//
//	停止
//
void CSoundMgr::Stop(sedata::SeNameList name)
{
	m_Sedata->Stop(name);
}

void CSoundMgr::SeVolume(float vol)
{
	m_Sedata->SetSeVolume(vol);
}

///////////////////////////////////////////////////////////
//
//	SEの音量
//
void CSoundMgr::Update()
{
	m_Bgmdata->Update();
}

///////////////////////////////////////////////////////////
//
//	SEのぴっち
//
void CSoundMgr::SetPitctlate(sedata::SeNameList numb, float late)
{
	m_Sedata->PitchRate(numb, late);
}
///////////////////////////////////////////////////////////
//
//	SEのReverbEffect
//
void CSoundMgr::SetReverbEffect(float walltype, float roomsize)
{
	m_Sedata->SetReverbSize(walltype, roomsize);
}
///////////////////////////////////////////////////////////
//
//	SEのReverbEffectの初期化
//
void CSoundMgr::OffEffect()
{
	m_Sedata->offsetReverbSize();
}