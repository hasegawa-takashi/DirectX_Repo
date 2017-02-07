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

	// 複数ある可能性があるもの
	ColBox GetCol(){ return Collison; }

private:
	SpriteBox spritebox[MAX_TEXTURE_TITLE];
	CSprite *sprite[MAX_TEXTURE_TITLE];

	ColBox Collison;

	// カメラ用のオブジェク
	CCamera *CameraObj;		// 型キャスト後のオブジェクト
	OBJMGR CameraObjMgr;	// 型キャスト前のオブジェクト

	bool PushFade;


};

