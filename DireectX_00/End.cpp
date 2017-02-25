#include "End.h"
#include"Title.h"
#include"Input.h"

CEnd::CEnd()
{
}


CEnd::~CEnd()
{
}

void CEnd::Init() {

	for (int loop = 0; loop < MAX_TEXTURE_END; ++loop)
	{
		sprite[loop] = new CSprite;
	}

	sprite[0]->CreateMakeVertex2DPolygon(_T("../data/Texture/GameOver.png"), 0, 0, 800, 600, 255);
	sprite[1]->CreateMakeVertex2DPolygon(_T("../data/Texture/PushEnter.png"), 0, 0, 800, 600, 255);

	fade = 255;
}

void CEnd::Update() {
	if (CInput::GetKeyPress(DIK_SPACE))
	{
		CSceneMgr::Instance()->ChangeScene(new CTitle);
	}

	if (fade >= 255)
		PushFade = true;
	else if (fade <= 0)
		PushFade = false;

	if (PushFade == true)
	{
		fade -= 5;
	}
	else{
		fade += 5;
	}

	sprite[1]->CreateMakeVertex2DPolygon(_T("../data/Texture/PushEnter.png"), 0.0f, 0.0f, 800.0f, 600.0f, (int)fade);

}

void CEnd::LateUpdate() {

}


void CEnd::Draw() {
	
}

void CEnd::LateDraw() {
	for (int i = 0; i < MAX_TEXTURE_END; i++)
		sprite[i]->Render();
}

void CEnd::Release() {
	for (int i = 0; i < MAX_TEXTURE_END; ++i)
	{
		sprite[i]->Release();

		delete sprite[i];
	}
}

void CEnd::Pause() {
	
}
