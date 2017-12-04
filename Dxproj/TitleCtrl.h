#pragma once
#include "includeheader.h"
#include"GameHeader.h"

class CSprite;
#include"Sprite.h"

class CTitleCtrl : public ObjBase
{
public:
	CTitleCtrl();
	~CTitleCtrl();

	void Update();
	void UIDraw();

private:

	bool m_PushSceneChange;
	static const int MAX_TEXTURE_TITLE = 1;
	CSprite* m_Sprite[MAX_TEXTURE_TITLE];

};

