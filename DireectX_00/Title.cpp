#include "Title.h"
#include"Input.h"
#include"GameMain.h"
#include"Camera.h"
#include"Title.h"
#include"TitleUI.h"
#include"Camera.h"

CTitle::CTitle() 
{

}


CTitle::~CTitle() 
{

}

void CTitle::Init() {


	CObjManager::Instance()->MonSter();

	CObjManager::Instance()->PushObj(new CTitleUI, ID_OTHER);

	CObjManager::Instance()->PushObj(new CCamera, ID_CAMERA);

	CObjManager::Instance()->Init();

}

void CTitle::Update() {

	if (CInput::GetKeyPress(DIK_SPACE))
	{
		CSceneMgr::Instance()->ChangeScene(new CGameMain);
	}

	CObjManager::Instance()->Update();

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

void CTitle::Pause() {
	// タイトルでポーズはないよ
}
