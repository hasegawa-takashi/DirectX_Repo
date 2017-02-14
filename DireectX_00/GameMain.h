#pragma once
#include"Scene.h"
#include"ObjManager.h"
#include"Camera.h"
#include"Player.h"
#include"EnemyMgr.h"
#include"Field.h"
#include"Sky.h"
#include"Goal.h"

class CGameMain :public CSceneBase
{
public:
	CGameMain();
	~CGameMain();


	// CSceneBass ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Draw() override;
	virtual void LateDraw() override;
	virtual void UIDraw() override;
	virtual void Release() override;
	virtual void Pause() override;

private:
};

