#pragma once

#include"Sprite.h"
#include<functional>
#include"Scene.h"

//////////////////////////////////////////////////////////////
//
//		FadeIn,Out�̃N���X
//
/////////////////////////////////////////////////////////////
class CFade : public ObjBase
{
public:

	CFade();
	~CFade();
	
	// Update
	void Update();
	// FADE�`��p
	void UIDraw();

protected:
	//==============================
	//	�ϐ�
	int Fadenum;		// ���݂�Fade
	CSprite *sprite;	// SpriteClass

	//==============================
	//	�֐�
	// FadeIn���ĂԃN���X
	void FadeIn() {};
	// FadeOut���ĂԃN���X
	void FadeOut() {};

	// function��Fade�p(�Ԃ�l����)
	std::function< void(void) > Fadefunc;
	
};