#pragma once

/// <summary>
/// 今更思ったけどこのシーンを書く作業何回も重複しててあれじゃないか？
/// って思い始めた、素直に面倒
/// </summary>

#include"includeheader.h"
#include"GameHeader.h"
#include"SoundInclude.h"

class CGameScene : public CSceneBase
{
public:
	CGameScene();
	~CGameScene();

	void Init();
	void Update();
	void LateUpdate();
	void Draw();
	void LateDraw();
	void UIDraw();
	void Release();
	void Pause();

private:


};

