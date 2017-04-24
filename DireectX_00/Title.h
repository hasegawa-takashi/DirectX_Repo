#pragma once
#include "Scene.h"
#include<stdio.h>
#include"Input.h"
#include"GameMain.h"
#include"Camera.h"
#include"Title.h"
#include"TitleUI.h"
#include"Camera.h"
#include"BlackoutFade.h"
#include"SoundSorce\SoundMgr.h"

class CTitle : public CSceneBase {
public:
	CTitle();
	virtual ~CTitle();

	// CSceneBass ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Draw() override;
	virtual void LateDraw() override;
	virtual void UIDraw() override;
	virtual void Release() override;

private:

};

