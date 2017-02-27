#pragma once

#include"Sprite.h"
#include<thread>

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
	int Fadenum;		// 現在のFade
	CSprite *sprite;	// SpriteClass

	//==============================
	//	関数
	// FadeInを呼ぶクラス
	void FadeIn();
	// FadeOutを呼ぶクラス
	void FadeOut();
	// threadのFade用
	std::thread Fadethread;
	

};
