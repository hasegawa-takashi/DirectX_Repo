#include "BlackoutFade.h"



CBlackoutFade::CBlackoutFade()
{
	Fadenum = 0;
	sprite = nullptr;
	sprite = new CSprite;
	sprite->CreateMakeVertex2DPolygon(PATH_FADETEXTURE, 0, 0, CWindowCreate::Getintance().GetSCREENWIDTH(), CWindowCreate::Getintance().GetSCREENHEIGHT(), Fadenum);
	m_NonDeleteObj = true;
	// èâä˙âª
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
	// FadeÇ÷à⁄çs
	if (Fadenum <= 0)
	{
		Fadenum = 0;
		// é©ï™Ç≈é©ï™ÇéEÇ∑
		CObjMgr::Getintance().PopObj(ID_FADE, m_ObjNumb);
	}
}

void CBlackoutFade::FadeOut()
{
	Fadenum += FADE_SPEED;
	// FadeèIóπ
	if (Fadenum >= MAX_FADE)
	{
		Fadenum = MAX_FADE;
		Fadefunc = std::bind(&CBlackoutFade::FadeIn, this);
		CSceneMgr::Getintance().ChangeScene();
	}
}