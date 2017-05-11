#include "Title.h"

CTitle::CTitle() 
{
	GetObjMgr()->PushObj(new CTitleUI, ID_OTHER);
	GetObjMgr()->PushObj(new CCamera, ID_CAMERA);
	
	PushEnter = false;
}


CTitle::~CTitle() 
{

}

void CTitle::Init() {

}

void CTitle::Update() {


	CObjManager::Instance()->Update();

	if (CInput::GetKeyPress(DIK_SPACE) && PushEnter == false )
	{
		GetSceneMgr()->PushScene<CGameMain>();
		GetObjMgr()->PushObj(new CBlackoutFade , ID_FADE);
		PushEnter = true;
	}

	// デバッグ
	if (CInput::GetKeyPress(DIK_S))
	{
		GetSoundMgr()->Stop(sedata::SE1);
	}
	if (CInput::GetKeyPress(DIK_D))
	{
		GetSoundMgr()->Play(sedata::SE1);
	}
	
	if (CInput::GetKeyPress(DIK_H))
	{
		GetSoundMgr()->SetReverbEffect(1.0f,0.0f);
	}
	if (CInput::GetKeyPress(DIK_J))
	{
		GetSoundMgr()->OffEffect();
	}

	/*if (CInput::GetKeyPress(DIK_UPARROW))
	{
		GetSoundMgr()->SeVolume(1.0f);
	}
	if (CInput::GetKeyPress(DIK_DOWNARROW))
	{
		GetSoundMgr()->SeVolume(0.5f);
	}
	
	if (CInput::GetKeyPress(DIK_LEFTARROW))
	{
		GetSoundMgr()->SetPitctlate(sedata::SE1,1.0f);
	}
	if (CInput::GetKeyPress(DIK_RIGHTARROW))
	{
		GetSoundMgr()->SetPitctlate(sedata::SE1, 0.5f);
	}*/



}

void CTitle::LateUpdate() {
	CObjManager::Instance()->LateUpdate();
}

void CTitle::Draw() {
	CObjManager::Instance()->Draw();
}

void CTitle::LateDraw() {
	CObjManager::Instance()->LateDraw();
}

void CTitle::UIDraw()
{
	CFPS::Instance()->Draw();
	CObjManager::Instance()->UIDraw();
}

void CTitle::Release() {
	CObjManager::Instance()->AllRelaseObj();
}