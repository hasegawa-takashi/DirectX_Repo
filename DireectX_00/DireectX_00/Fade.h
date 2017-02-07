#pragma once

#include"Sprite.h"

class CFade
{
public:

	~CFade();

	bool FadeIn();

	bool FadeOut();

	void DrawFade();

	static CFade* Instance(){
		static CFade _Instance;
		return &_Instance;
	}

	void SetFade();

private:

	bool FadeInflag;
	bool FadeOutflag;

	CFade();

	SpriteBox spritebox;

	CSprite *sprite;

};

