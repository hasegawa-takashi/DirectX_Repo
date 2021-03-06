#pragma once

#include"SceneMgr.h"
class CSprite;
#include"Sprite.h"
#include<functional>


//////////////////////////////////////////////////////////////
//
//		FadeIn,Outのクラス
//
/////////////////////////////////////////////////////////////
class CFade : public ObjBase
{
public:

	CFade();
	~CFade();
	
	// Update
	void Update();
	// FADE描画用
	void UIDraw();

protected:
	//==============================
	//	変数
	int Fadenum;		// 現在のFade
	CSprite *m_Sprite;	// SpriteClass

	//==============================
	//	関数
	// FadeInを呼ぶクラス
	void FadeIn() {};
	// FadeOutを呼ぶクラス
	void FadeOut() {};

	// functionのFade用(返り値無し)
	std::function< void(void) > Fadefunc;
	
};