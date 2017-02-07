#pragma once
#include "ObjManager.h"
#include"Sprite.h"
#include"Camera.h"

#define MAX_TEXTURE_TITLE 2

class CTitleUI : public ObjBase
{
public:
	CTitleUI();
	~CTitleUI();

	void Init();
	void Update();
	void LateUpdate();
	void Draw();
	void LateDraw();
	void UIDraw();
	void Release();
	void Pause();
	bool AllRelaseObj();

	// ��������\�����������
	ColBox GetCol(){ return Collison; }

private:
	SpriteBox spritebox[MAX_TEXTURE_TITLE];
	CSprite *sprite[MAX_TEXTURE_TITLE];

	ColBox Collison;

	// �J�����p�̃I�u�W�F�N
	CCamera *CameraObj;		// �^�L���X�g��̃I�u�W�F�N�g
	OBJMGR CameraObjMgr;	// �^�L���X�g�O�̃I�u�W�F�N�g

	bool PushFade;


};

