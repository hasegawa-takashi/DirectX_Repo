#include "BlackoutFade.h"



CBlackoutFade::CBlackoutFade()
{
	Fadenum = 0;
	sprite = nullptr;
	sprite = new CSprite;
	sprite->CreateMakeVertex2DPolygon(PATH_FADETEXTURE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fadenum);
	ObjNumb = GetObjMgr()->RenameObj(ID_FADE, ObjID);
	NonDeleteObj = true;
	// ������
	Fadefunc = std::bind(&CBlackoutFade::FadeOut, this);
}


CBlackoutFade::~CBlackoutFade()
{
	Fadefunc.~function();
	delete sprite;
}

void CBlackoutFade::FadeIn()
{
	Fadenum -= FADE_SPEED;
	// Fade�ֈڍs
	if (Fadenum <= 0)
	{
		Fadenum = 0;
		// �����Ŏ������E��
		GetObjMgr()->PopObj(ID_FADE, ObjNumb);
	}
}

void CBlackoutFade::FadeOut()
{
	Fadenum += FADE_SPEED;
	// Fade�I��
	if (Fadenum >= MAX_FADE)
	{
		Fadenum = MAX_FADE;
		Fadefunc = std::bind(&CBlackoutFade::FadeIn, this);
		GetSceneMgr()->ChangeScene();
	}
}