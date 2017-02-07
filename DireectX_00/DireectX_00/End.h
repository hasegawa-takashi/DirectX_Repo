#pragma once
#include "Scene.h"


#define MAX_TEXTURE_END 2

class CEnd :
	public CSceneBase
{
public:
	CEnd();
	~CEnd();

	// CSceneBass ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Draw() override;
	virtual void LateDraw() override;
	virtual void UIDraw(){};
	virtual void Release() override;
	virtual void Pause() override;

private:

	CSprite *sprite[MAX_TEXTURE_END];

	float fade;

	bool PushFade;
};

