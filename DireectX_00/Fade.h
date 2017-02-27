#pragma once

#include"Sprite.h"
#include<thread>

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
	void FadeIn();
	// FadeOut���ĂԃN���X
	void FadeOut();
	// thread��Fade�p
	std::thread Fadethread;
	

};
