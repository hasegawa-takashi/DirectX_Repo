#pragma once
#include "Scene.h"
#include"ObjManager.h"

class CSceneBase;
class CGameMain :public CSceneBase
{
public:
	CGameMain();
	~CGameMain();


	// CSceneBass ����Čp������܂���
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

