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
//	������
//
void CSoundMgr::Init()
{
	m_Bgmdata = new CBgmDatabase();
	m_Sedata = new CSEDatabase();
}

///////////////////////////////////////////////////////////
//
//	�Đ�
//
void CSoundMgr::Play(bgmdata::BgmNameList name, bool fadein)
{
	m_Bgmdata->Play(name,fadein);
}

///////////////////////////////////////////////////////////
//
//	��~
//
void CSoundMgr::Stop(bgmdata::BgmNameList name, bool fadeout)
{
	m_Bgmdata->Stop(name, fadeout);
}

///////////////////////////////////////////////////////////
//
//	BGM�̉���
//
void CSoundMgr::BgmVolume(float vol)
{
	m_Bgmdata->SetBgmVolume(vol);
}

///////////////////////////////////////////////////////////
//
//	BGM�̃s�b�`���[�g
//
void CSoundMgr::SetPitctlate(bgmdata::BgmNameList numb, float late)
{
	m_Bgmdata->PitchRate(numb, late);
}

///////////////////////////////////////////////////////////
//
//	�Đ�
//
void CSoundMgr::Play(sedata::SeNameList name)
{
	m_Sedata->Play(name);
}

///////////////////////////////////////////////////////////
//
//	��~
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
//	SE�̉���
//
void CSoundMgr::Update()
{
	m_Bgmdata->Update();
}

///////////////////////////////////////////////////////////
//
//	SE�̂҂���
//
void CSoundMgr::SetPitctlate(sedata::SeNameList numb, float late)
{
	m_Sedata->PitchRate(numb, late);
}
///////////////////////////////////////////////////////////
//
//	SE��ReverbEffect
//
void CSoundMgr::SetReverbEffect(float walltype, float roomsize)
{
	m_Sedata->SetReverbSize(walltype, roomsize);
}
///////////////////////////////////////////////////////////
//
//	SE��ReverbEffect�̏�����
//
void CSoundMgr::OffEffect()
{
	m_Sedata->offsetReverbSize();
}