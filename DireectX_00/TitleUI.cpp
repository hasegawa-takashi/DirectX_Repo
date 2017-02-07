#include "TitleUI.h"


CTitleUI::CTitleUI()
{
}


CTitleUI::~CTitleUI()
{
}

void CTitleUI::Init()
{


	for (int loop = 0; loop < MAX_TEXTURE_TITLE; ++loop)
	{

		sprite[loop] = new CSprite;
		sprite[loop]->Init();

		sprite[loop]->CreateMakeVertex2DPolygon(_T("../data/Texture/title.png"), 0, 0, 800, 600, 255);
		sprite[loop]->CreateMakeVertex2DPolygon(_T("../data/Texture/PushEnter.png"), 0, 0, 800, 600, 255);


	}
	CObjManager::Instance()->SerchObj(ID_CAMERA, CameraObjMgr);
	if (!CameraObjMgr.empty())
	{
		ObjBase* hoge = CameraObjMgr.begin()->second;
		CameraObj = dynamic_cast<CCamera*>(hoge);

		CameraObj->SetCameraType(Cam_PREVIEW);
	}
}

void CTitleUI::Update()
{
	if (spritebox[1].Fade >= 255)
		PushFade = true;
	else if (spritebox[1].Fade <= 0)
		PushFade = false;

	if (PushFade == true)
	{
		spritebox[1].Fade -= 10;
	}
	else{
		spritebox[1].Fade += 10;
	}

	for (int loop = 0; loop < MAX_TEXTURE_TITLE; ++loop)
	{
		sprite[loop]->CreateMakeVertex2DPolygon(_T("../data/Texture/PushEnter.png"), 0, 0, 800, 600, spritebox[1].Fade);
	}
}

void CTitleUI::LateUpdate()
{

}

void CTitleUI::Draw()
{

}

void CTitleUI::LateDraw()
{
	
}

void CTitleUI::UIDraw()
{
	for (int i = 0; i < MAX_TEXTURE_TITLE; i++)
		sprite[i]->Render();
}

void CTitleUI::Release()
{
	for (int i = 0; i < MAX_TEXTURE_TITLE; ++i)
	{
		sprite[i]->Release();
		delete sprite[i];
	}
}

void CTitleUI::Pause()
{
	
}

bool CTitleUI::AllRelaseObj()
{
	return false;
}