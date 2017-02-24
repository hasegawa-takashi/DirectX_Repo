#pragma once

#include"Sprite.h"

//////////////////////////////////////////////////////////////
//
//		FadeIn,Outのクラス
//
/////////////////////////////////////////////////////////////
class CFade : public ObjBase
{
public:

	~CFade();
	CFade();

	// Update
	void Update();
	// FADE描画用
	void UIDraw();

private:
	//==============================
	//	変数
	int Fadenum;	// 現在のFade
	// SpriteClass
	CSprite *sprite;

	//==============================
	//	関数
	// FadeInを呼ぶクラス
	bool FadeIn();
	// FadeOutを呼ぶクラス
	bool FadeOut();

};
