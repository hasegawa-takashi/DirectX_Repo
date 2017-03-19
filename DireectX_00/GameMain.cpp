#include "GameMain.h"

CGameMain::CGameMain()
{
	CObjManager::Instance()->PushObj(new CCamera, ID_CAMERA);
	CObjManager::Instance()->PushObj(new Player, ID_PLAYER);
	CObjManager::Instance()->PushObj(new CEnemyMgr, ID_ENEMY);
	//CObjManager::Instance()->PushObj(new CField, ID_FIELD);
	//CObjManager::Instance()->PushObj(new CSky, ID_OTHER);		// メモリーリーク 一時コメントアウト
	//CObjManager::Instance()->PushObj(new CGoal, ID_GOAL);
}


CGameMain::~CGameMain()
{
}

void CGameMain::Init() {
	// 初期オブジェクトの設定一気に設定するよ
	CObjManager::Instance()->Init();
}

void CGameMain::Update() {
	CObjManager::Instance()->Update();
	
}

void CGameMain::LateUpdate() {
	CObjManager::Instance()->LateUpdate();
	
}

void CGameMain::Draw() {
	CObjManager::Instance()->Draw();
	
}

void CGameMain::LateDraw() {
	CObjManager::Instance()->LateDraw();
	
}

void CGameMain::UIDraw() {
	CFPS::Instance()->Draw();
	CObjManager::Instance()->UIDraw();
}


void CGameMain::Release() {
	CObjManager::Instance()->Release();
}

void CGameMain::Pause() {
}
