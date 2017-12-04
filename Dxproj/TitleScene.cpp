#include "TitleScene.h"



CTitleScene::CTitleScene()
{
	CObjMgr::Getintance().PushObj(new CTitleCtrl, ID_OTHER);
	CObjMgr::Getintance().PushObj(new CPlayer, ID_PLAYER);
	CObjMgr::Getintance().PushObj(new CSkybox, ID_OTHER);
}


CTitleScene::~CTitleScene()
{
}

void CTitleScene::Init()
{
	if (m_Initflag == true)
	{
		return;
	}

	CObjMgr::Getintance().Init();
	CCamera::Getintance().Init();
	m_Initflag = true;
}

void CTitleScene::Update()
{
	CObjMgr::Getintance().Update();
}

void CTitleScene::LateUpdate()
{
	CObjMgr::Getintance().LateUpdate();
}

void CTitleScene::Draw()
{
	CObjMgr::Getintance().Draw();
}

void CTitleScene::LateDraw()
{
	CObjMgr::Getintance().LateDraw();
}

void CTitleScene::UIDraw()
{
	CObjMgr::Getintance().UIDraw();
}

void CTitleScene::Release()
{
	CObjMgr::Getintance().Release();
}