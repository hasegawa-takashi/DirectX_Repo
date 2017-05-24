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
//	�Đ�(3D����)
//
void CSoundMgr::Play(bgmdata::BgmNameList, bool fadeout, D3DXMATRIX emitter)
{

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
	m_Bgmdata->SetMasterVolume(vol);
}

///////////////////////////////////////////////////////////
//
//	BGM�̃s�b�`���[�g
//
void CSoundMgr::SetPitctlate(bgmdata::BgmNameList numb, float late)
{
	m_Bgmdata->ChangePitch(numb, late);
}


void CSoundMgr::SetReverbEffect(bgmdata::BgmNameList numb, float walltype, float roomsize)
{
	m_Bgmdata->ChangeReverv(numb,walltype,roomsize);
}

void CSoundMgr::SetEchoEffect(bgmdata::BgmNameList numb, float Delay, float feedback, float wetdry)
{
	m_Bgmdata->ChangeEcho(numb,Delay,feedback, wetdry);
}

void CSoundMgr::OffBGMReverb()
{
	m_Bgmdata->OffReverv();
}

void CSoundMgr::OffBGMEcho()
{
	m_Bgmdata->OffEcho();
}

///////////////////////////////////////////////////////////
//
//	�Đ�
//
void CSoundMgr::Play(sedata::SeNameList name, bool fadein)
{
	m_Sedata->Play(name,fadein);
}

///////////////////////////////////////////////////////////
//
//	�Đ�(3DSound)
//
void CSoundMgr::Play(sedata::SeNameList, bool fadein, D3DXMATRIX emitter)
{

}

///////////////////////////////////////////////////////////
//
//	��~
//
void CSoundMgr::Stop(sedata::SeNameList name, bool fadeout)
{
	m_Sedata->Stop(name,fadeout);
}

void CSoundMgr::SeVolume(float vol)
{
	m_Sedata->SetMasterVolume(vol);
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
	m_Sedata->ChangePitch(numb, late);
}
///////////////////////////////////////////////////////////
//
//	SE��ReverbEffect
//
void CSoundMgr::SetReverbEffect(sedata::SeNameList numb,float walltype, float roomsize)
{
	m_Sedata->ChangeReverv(numb,walltype, roomsize);
}
///////////////////////////////////////////////////////////
//
//	SE��ReverbEffect�̏�����
//
void CSoundMgr::OffSEReverb()
{
	m_Sedata->OffReverv();
}
///////////////////////////////////////////////////////////
//
//	SE��Echo�̐ݒ�
//
void CSoundMgr::SetEchoEffect(sedata::SeNameList numb, float Delay, float feedback, float wetdry)
{
	m_Sedata->ChangeEcho(numb,Delay,feedback,wetdry);
}
///////////////////////////////////////////////////////////
//
//	SE��EchoEffect�̏�����
//
void CSoundMgr::OffSEEcho()
{
	m_Sedata->OffEcho();
}