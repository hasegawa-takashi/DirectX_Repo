#pragma once

/// <summary>
/// ���X�v�������ǂ��̃V�[����������Ɖ�����d�����ĂĂ��ꂶ��Ȃ����H
/// ���Ďv���n�߂��A�f���ɖʓ|
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

