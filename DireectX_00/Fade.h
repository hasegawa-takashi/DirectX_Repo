#pragma once

#include"Sprite.h"

//////////////////////////////////////////////////////////////
//
//		FadeIn,Out�̃N���X
//
/////////////////////////////////////////////////////////////
class CFade : public ObjBase
{
public:

	~CFade();
	CFade();

	// Update
	void Update();
	// FADE�`��p
	void UIDraw();

private:
	//==============================
	//	�ϐ�
	int Fadenum;	// ���݂�Fade
	// SpriteClass
	CSprite *sprite;

	//==============================
	//	�֐�
	// FadeIn���ĂԃN���X
	bool FadeIn();
	// FadeOut���ĂԃN���X
	bool FadeOut();

};
