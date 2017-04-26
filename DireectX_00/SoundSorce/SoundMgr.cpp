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

void CSoundMgr::Play(bgmdata::BgmNameList name)
{
	m_Bgmdata->Play(name);
}

void CSoundMgr::Update()
{
	m_Bgmdata->Update();
}
