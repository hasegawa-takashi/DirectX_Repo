#pragma once
//=============================================================================
//
// window処理 [window.h]
//
//=============================================================================
#ifndef _GAMEWND_H_
#define _GAMEWND_H_

//=============================================================================
//	インクルード
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
// マクロ定義
//=============================================================================


//=============================================================================
// class定義
//=============================================================================

class CGameWnd{

private:

	bool m_bWinmode;						//フルスクリーンorウインドウズ

	CGameWnd(){};							//デストラクタ1
	MSG msg;

	// === FPS用 === //
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