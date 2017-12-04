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
	// FADE�`��p
	void UIDraw();

private:

	//==============================
	//	�ϐ�
	int m_Fadenum;		// ���݂�Fade
	CSprite *m_Sprite;	// SpriteClass

	//==============================
	//	�֐�
	// FadeIn���ĂԃN���X

	// FadeIn���ĂԃN���X
	void FadeIn();
	// FadeOut���ĂԃN���X
	void FadeOut();

	// function��Fade�p(�Ԃ�l����)
	std::function< void(void) > m_Fadefunc;

};

