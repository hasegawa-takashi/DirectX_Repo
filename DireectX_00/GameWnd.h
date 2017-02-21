#pragma once
//=============================================================================
//
// window���� [window.h]
//
//=============================================================================
#ifndef _GAMEWND_H_
#define _GAMEWND_H_

//=============================================================================
//	�C���N���[�h
//=============================================================================
#include"Window.h"
#include"Scene.h"
#include"ObjManager.h"
#include"FPS.h"
#include"Input.h"
#include"Title.h"
#include"Sprite.h"
#include"mleak.h"

//=============================================================================
// �}�N����`
//=============================================================================


//=============================================================================
// class��`
//=============================================================================

class CGameWnd{

private:

	bool m_bWinmode;						//�t���X�N���[��or�E�C���h�E�Y

	CGameWnd(){};							//�f�X�g���N�^1
	MSG msg;

	// === FPS�p === //
	int FpsCnt;

public:

	static CGameWnd* Instance(){
		static CGameWnd _Instance;
		return &_Instance;
	}

	bool Init(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int iCmdShow);
	void Release(HINSTANCE hInstance);
	void Run();

	~CGameWnd(){};
protected:

};



#endif