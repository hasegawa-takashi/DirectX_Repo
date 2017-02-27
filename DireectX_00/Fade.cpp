#include "Fade.h"

#define PATH_FADETEXTURE _T("../data/Texture/Fade.png")
const int MAX_FADE = 255;
const float FADE_SPEED = 1.0f;

CFade::CFade()
{
	


	Fadenum = 255;

	sprite->CreateMakeVertex2DPolygon(
		PATH_FADETEXTURE,
		0,
		0,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		Fadenum);

	ObjNumb = GetObjMgr()->RenameObj(ID_FADE);
	NonDeleteObj = true;
}


CFade::~CFade()
{
	delete sprite;
}


// Update
void CFade::Update()
{
	sprite->SetFade(Fadenum);
}

// FADE•`‰æ—p
void CFade::UIDraw()
{
	sprite->Render();
}

void CFade::FadeIn()
{
	Fadenum -= (int)FADE_SPEED;

	sprite->SetFade(Fadenum);

	if (Fadenum <= 0)
	{
		Fadenum = 0;
	}

}

void CFade::FadeOut()
{
	Fadenum += (int)FADE_SPEED;
	sprite->SetFade(Fadenum);

	if (Fadenum >= 255)
	{
		Fadenum = 255;
		// Ž©•ª‚ÅŽ©•ª‚ðŽE‚·
		GetObjMgr()->PopObj(ObjNumb, ID_FADE);

	}

}