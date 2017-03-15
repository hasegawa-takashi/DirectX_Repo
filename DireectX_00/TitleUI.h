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

private:
	CSprite *sprite[MAX_TEXTURE_TITLE];

	// �J�����p�̃I�u�W�F�N
	CCamera *CameraObj;				// �^�L���X�g��̃I�u�W�F�N�g
	std::list<ObjBase*> CameraList;	// �J������list�̎擾

	bool PushFade;

	int fade[MAX_TEXTURE_TITLE];
};

