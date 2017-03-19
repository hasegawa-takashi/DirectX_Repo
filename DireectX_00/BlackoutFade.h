#pragma once
#include "Fade.h"

const int MAX_FADE = 255;
const int FADE_SPEED = 3.0f;
#define PATH_FADETEXTURE _T("../data/Texture/Fade.png")


class CBlackoutFade : public CFade
{
public:
	CBlackoutFade();
	~CBlackoutFade();

	void Init() {};

	// Update
	void Update() {
		sprite->SetFade(Fadenum);
		Fadefunc();
	};
	// FADE描画用
	void UIDraw() { sprite->Render(); };

private:

	//==============================
	//	関数
	// FadeInを呼ぶクラス

	// FadeInを呼ぶクラス
	void FadeIn();
	// FadeOutを呼ぶクラス
	void FadeOut();

};

