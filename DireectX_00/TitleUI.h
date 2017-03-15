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

	// カメラ用のオブジェク
	CCamera *CameraObj;				// 型キャスト後のオブジェクト
	std::list<ObjBase*> CameraList;	// カメラのlistの取得

	bool PushFade;

	int fade[MAX_TEXTURE_TITLE];
};

