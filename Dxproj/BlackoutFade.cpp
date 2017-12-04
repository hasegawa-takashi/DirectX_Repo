#include "BlackoutFade.h"



CBlackoutFade::CBlackoutFade()
{
	m_Fadenum = 0;
	m_Sprite = nullptr;
	m_Sprite = new CSprite;
	m_Sprite->CreateMakeVertex2DPolygon(PATH_FADETEXTURE, 0.0f, 0.0f, CWindowCreate::Getintance().GetSCREENWIDTH(), CWindowCreate::Getintance().GetSCREENHEIGHT(), m_Fadenum);
	m_NonDeleteObj = true;
	// èâä˙âª
	m_Fadefunc = std::bind(&CBlackoutFade::FadeOut, this);
}


CBlackoutFade::~CBlackoutFade()
{
	m_Fadefunc.~function();
	delete m_Sprite;
}

void CBlackoutFade::Init()
{

}

void CBlackoutFade::Update() {
	m_Sprite->SetFade(m_Fadenum);
	m_Fadefunc();
}

void CBlackoutFade::UIDraw()
{ 
	m_Sprite->Render(); 
}

void CBlackoutFade::FadeIn()
{
	m_Fadenum -= FADE_SPEED;
	// FadeÇ÷à⁄çs
	if (m_Fadenum <= 0)
	{
		m_Fadenum = 0;
		// é©ï™Ç≈é©ï™ÇéEÇ∑
		CObjMgr::Getintance().PopObj(ID_FADE, m_ObjNumb);
	}
}

void CBlackoutFade::FadeOut()
{
	m_Fadenum += FADE_SPEED;
	// FadeèIóπ
	if (m_Fadenum >= MAX_FADE)
	{
		m_Fadenum = MAX_FADE;
		m_Fadefunc = std::bind(&CBlackoutFade::FadeIn, this);
		CSceneMgr::Getintance().ChangeScene();
	}
}