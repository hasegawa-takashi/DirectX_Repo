#include "Fade.h"

#define PATH_FADETEXTURE _T("../data/Texture/Fade.png")
const int MAX_FADE = 255;
const float FADE_SPEED = 1.0f;

CFade::CFade()
{
	Fadenum = 255;

	sprite = nullptr;
	sprite = new CSprite;

	sprite->CreateMakeVertex2DPolygon(PATH_FADETEXTURE,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,Fadenum);

	ObjNumb = GetObjMgr()->RenameObj(ID_FADE, ObjID);
	NonDeleteObj = true;

	// ‰Šú‰»
	Fadefunc = std::bind(&CFade::FadeIn,this);

}


CFade::~CFade()
{
	Fadefunc.~function();
	delete sprite;
}


// Update
void CFade::Update()
{
	sprite->SetFade(Fadenum);
	Fadefunc();
}

// FADE•`‰æ—p
void CFade::UIDraw()
{
	sprite->Render();
}

void CFade::FadeIn()
{
	Fadenum -= (int)FADE_SPEED;

	//sprite->SetFade(Fadenum);

	if (Fadenum <= 0)
	{
		Fadefunc = std::bind(&CFade::FadeOut, this);
		Fadenum = 0;
	}
}

void CFade::FadeOut()
{

	while (true)
	{
		Fadenum += (int)FADE_SPEED;
		//prite->SetFade(Fadenum);

		// FadeI—¹
		if (Fadenum >= 255)
		{
			Fadenum = 255;
			// Ž©•ª‚ÅŽ©•ª‚ðŽE‚·
			GetObjMgr()->PopObj(ID_FADE, ObjNumb);
			break;
		}
	}
}