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
		auto p = new CSprite;
		sprite[loop] = p;
	}

	fade[0] = 255;
	sprite[0]->CreateMakeVertex2DPolygon(_T("../data/Texture/title.png"), 0, 0, 800, 600, fade[0]);
	fade[1] = 255;
	sprite[1]->CreateMakeVertex2DPolygon(_T("../data/Texture/PushEnter.png"), 0, 0, 800, 600, fade[1]);

	
	// カメラオブジェクトのしゅとく
	CameraList = GetObjMgr()->SerchObj(ID_CAMERA);
	
	for (auto& p : CameraList)
	{
		// Cameraの完全取得
		CameraObj = dynamic_cast<CCamera*>(p);
		CameraObj->SetCameraType(Cam_PREVIEW);
	}


}

void CTitleUI::Update()
{
	if (fade[1] >= 255)
		PushFade = true;
	else if (fade[1] <= 0)
		PushFade = false;

	if (PushFade == true)
	{
		fade[1] -= 10;
	}
	else if(PushFade == false) {
		fade[1] += 10;
	}

	for (int loop = 0; loop < MAX_TEXTURE_TITLE; ++loop)
	{
		sprite[loop]->SetFade(fade[loop]);
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
}

void CTitleUI::Pause()
{
	
}

bool CTitleUI::AllRelaseObj()
{

	for (int i = 0; i < MAX_TEXTURE_TITLE; ++i)
	{
		if (sprite[i] != NULL)
		{
			sprite[i]->Release();
			auto p = sprite[i];
			delete sprite[i];
			sprite[i] = NULL;
		}
	}

	return true;
}