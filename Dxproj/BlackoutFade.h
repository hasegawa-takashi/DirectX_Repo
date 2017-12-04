#pragma once
class CSprite;
#include"includeheader.h"

const int MAX_FADE = 255;
const int FADE_SPEED = 1;
#define PATH_FADETEXTURE _T("../data/Texture/Fade.png")

class CBlackoutFade : public ObjBase
{
public:
	CBlackoutFade();
	~CBlackoutFade();

	void Init();

	// Update
	void Update();
	// FADE描画用
	void UIDraw();

private:

	//==============================
	//	変数
	int m_Fadenum;		// 現在のFade
	CSprite *m_Sprite;	// SpriteClass

	//==============================
	//	関数
	// FadeInを呼ぶクラス

	// FadeInを呼ぶクラス
	void FadeIn();
	// FadeOutを呼ぶクラス
	void FadeOut();

	// functionのFade用(返り値無し)
	std::function< void(void) > m_Fadefunc;

};

