#include "SoundMgr.h"



CSoundMgr::CSoundMgr()
{

}


CSoundMgr::~CSoundMgr()
{

}

void CSoundMgr::Init()
{
	m_Bgmdata = new CBgmDatabase();
	m_Sedata = new CSEDatabase();
}

void CSoundMgr::Play(bgmdata::BgmNameList name, bool fadein = false)
{
	m_Bgmdata->Play(name,fadein);
}

void CSoundMgr::Stop(bgmdata::BgmNameList name, bool fadeout = false)
{
	m_Bgmdata->Stop(name, fadeout);
}

void CSoundMgr::Update()
{
	m_Bgmdata->Update();
}


void CSoundMgr::Play(sedata::SeNameList name)
{
	m_Sedata->Play(name);
}

void CSoundMgr::Stop(sedata::SeNameList name)
{
	m_Sedata->Stop(name);
}