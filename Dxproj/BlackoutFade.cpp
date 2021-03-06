#include "BlackoutFade.h"



CBlackoutFade::CBlackoutFade()
{
	m_Fadenum = 0;
	m_Sprite = nullptr;
	m_Sprite = new CSprite;
	m_Sprite->CreateMakeVertex2DPolygon(PATH_FADETEXTURE, 0.0f, 0.0f, CWindowCreate::Getintance().GetSCREENWIDTH(), CWindowCreate::Getintance().GetSCREENHEIGHT(), m_Fadenum);
	m_NonDeleteObj = true;
	// 初期化
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
	// Fadeへ移行
	if (m_Fadenum <= 0)
	{
		m_Fadenum = 0;
		// 自分で自分を殺す
		CObjMgr::Getintance().PopObj(ID_FADE, m_ObjNumb);
	}
}

void CBlackoutFade::FadeOut()
{
	m_Fadenum += FADE_SPEED;
	// Fade終了
	if (m_Fadenum >= MAX_FADE)
	{
		m_Fadenum = MAX_FADE;
		m_Fadefunc = std::bind(&CBlackoutFade::FadeIn, this);
		CSceneMgr::Getintance().ChangeScene();
	}
}