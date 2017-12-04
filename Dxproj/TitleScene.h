#pragma once
#include "includeheader.h"
class CTitleScene : public CSceneBase
{
public:
	CTitleScene();
	~CTitleScene();

	void Init();
	void Update();
	void LateUpdate();
	void Draw();
	void LateDraw();
	void UIDraw();
	void Release();
	void Pause() {};

};

