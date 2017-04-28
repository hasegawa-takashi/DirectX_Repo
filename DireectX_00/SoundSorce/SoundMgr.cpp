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
