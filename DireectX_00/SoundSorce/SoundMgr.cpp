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
//	再生(3D音声)
//
void CSoundMgr::Play(bgmdata::BgmNameList, bool fadeout, D3DXMATRIX emitter)
{

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
	m_Bgmdata->SetMasterVolume(vol);
}

///////////////////////////////////////////////////////////
//
//	BGMのピッチレート
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
//	再生
//
void CSoundMgr::Play(sedata::SeNameList name, bool fadein)
{
	m_Sedata->Play(name,fadein);
}

///////////////////////////////////////////////////////////
//
//	再生(3DSound)
//
void CSoundMgr::Play(sedata::SeNameList, bool fadein, D3DXMATRIX emitter)
{

}

///////////////////////////////////////////////////////////
//
//	停止
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
	m_Sedata->ChangePitch(numb, late);
}
///////////////////////////////////////////////////////////
//
//	SEのReverbEffect
//
void CSoundMgr::SetReverbEffect(sedata::SeNameList numb,float walltype, float roomsize)
{
	m_Sedata->ChangeReverv(numb,walltype, roomsize);
}
///////////////////////////////////////////////////////////
//
//	SEのReverbEffectの初期化
//
void CSoundMgr::OffSEReverb()
{
	m_Sedata->OffReverv();
}
///////////////////////////////////////////////////////////
//
//	SEのEchoの設定
//
void CSoundMgr::SetEchoEffect(sedata::SeNameList numb, float Delay, float feedback, float wetdry)
{
	m_Sedata->ChangeEcho(numb,Delay,feedback,wetdry);
}
///////////////////////////////////////////////////////////
//
//	SEのEchoEffectの初期化
//
void CSoundMgr::OffSEEcho()
{
	m_Sedata->OffEcho();
}