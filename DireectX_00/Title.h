#pragma once
#include "Scene.h"
#include<stdio.h>


class CTitle : public CSceneBase {
public:
	CTitle();
	virtual ~CTitle();

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

