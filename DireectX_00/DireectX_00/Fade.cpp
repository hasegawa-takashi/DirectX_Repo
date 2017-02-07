#include "Fade.h"


#define PATH_FADETEXTURE	_T("../data/Texture/Fade.png")
#define MAX_FADE	(255)
#define FADE_SPEED	(1.0f)

CFade::CFade()
{
	

}


CFade::~CFade()
{
	delete sprite;

}

bool CFade::FadeIn()
{
	if (!FadeInflag)
		return true;

	
	spritebox.Fade -= (int)FADE_SPEED;

	sprite->CreateMakeVertex2DPolygon(
		PATH_FADETEXTURE,
		0,
		0,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		spritebox.Fade);

	if (spritebox.Fade <= 0)
	{
		spritebox.Fade = 0;
		FadeInflag = false;

		return true;
	}

	return false;

}

bool CFade::FadeOut()
{
	if (!FadeOutflag)
		return true;

	for (int loop = 0; loop < MAX_FADE; loop++)
	{

		spritebox.Fade += (int)FADE_SPEED;

		sprite->CreateMakeVertex2DPolygon(
			PATH_FADETEXTURE,
			0,
			0,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			spritebox.Fade);

		if (spritebox.Fade >= 255)
		{
			spritebox.Fade = 255;
			FadeInflag = true;
			FadeOutflag = false;
			return true;
		}

		DrawFade();

	}
	return false;

}

void CFade::DrawFade()
{
	//CWindow::Instance()->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(128, 128, 255), 1.0f, 0); 
	
	if (FadeOutflag || FadeInflag)
	{

		if (SUCCEEDED(CWindow::Instance()->GetDevice()->BeginScene()))
		{

			// “§‰ß‚·‚é•û
			CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			sprite->Render();

			CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


			CWindow::Instance()->GetDevice()->EndScene();
		}
		CWindow::Instance()->GetDevice()->Present(NULL, NULL, NULL, NULL);
	}



}

void CFade::SetFade()
{
	sprite = new CSprite();

	sprite->CreateMakeVertex2DPolygon(
		PATH_FADETEXTURE,
		0,
		0,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0);

	FadeOutflag = true;
}