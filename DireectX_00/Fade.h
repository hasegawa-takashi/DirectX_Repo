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
	int Fadenum;		// ���݂�Fade
	CSprite *sprite;	// SpriteClass

	//==============================
	//	�֐�
	// FadeIn���ĂԃN���X
	bool FadeIn();
	// FadeOut���ĂԃN���X
	bool FadeOut();

};
