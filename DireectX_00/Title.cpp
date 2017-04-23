#include "Title.h"

CTitle::CTitle() 
{
	GetObjMgr()->PushObj(new CTitleUI, ID_OTHER);
	GetObjMgr()->PushObj(new CCamera, ID_CAMERA);
	
	GetSoundMgr()->Play(bgmdata::Sound1);
}


CTitle::~CTitle() 
{

}

void CTitle::Init() {

}

void CTitle::Update() {


	CObjManager::Instance()->Update();

	if (CInput::GetKeyPress(DIK_SPACE))
	{
		GetSceneMgr()->PushScene<CGameMain>();
		GetObjMgr()->PushObj(new CBlackoutFade , ID_FADE);
		//OutputDebugString("PushEnter\n");
	}


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