//=============================================================================
// インクルード
//=============================================================================
#include "GameWnd.h"
#include<tchar.h>
#include"Title.h"
#include"Sprite.h"
#include"mleak.h"

//=============================================================================
// Define
//=============================================================================
#define FRAME_RATE		(1000/60)	// フレームレート

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル宣言
//=============================================================================

//=============================================================================
// ゲームの初期化
//=============================================================================
bool CGameWnd::Init(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int iCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_CrtSetBreakAlloc(193);
	
	// 変数宣言
	HRESULT Createflag = E_FAIL;
	FpsCnt = 0;

	// インスタンスの前置き
	window = CWindow::Instance();
	// ウインドウの作成とD3Dデバイスの初期化
	Createflag = window->MakeWin(hInstance, hPrevInst, lpCmdLine, iCmdShow);
	if (Createflag == E_FAIL)return false;

	CInput::Init(window->GethwndDevice());

	// 入力コンテキストを指定されたウィンドウに関連付けます
	//::ImmAssociateContext(window->GethwndDevice(), NULL);
	
	// Windowのスクリーンモードの設定(今は出来ないただの木偶です)
	
	// タイマの分解能をセット
	timeBeginPeriod(1);

	// インスタンスの初期化
	CSceneMgr::Instance()->Init();

	// 一番最初のタイトルのプッシュ
	CSceneMgr::Instance()->PushScene(new CTitle);

	// Objマネージャーの初期化
	CObjManager::Instance()->Init();

	// 描画用マネージャーの初期化
	CFPS::Instance()->Init();

	CDebug::Instance()->Init();

	return true;

}

void CGameWnd::Run()
{

	// ゲームメインループ
	while (1)
	{
		

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{

			CFPS::Instance()->Update();
			FpsCnt= CFPS::Instance()->SetFps();
			
			if ((FpsCnt) >= (1000 / 60))
			{
				CSceneMgr::Instance()->Update();
				CInput::Update();
				CSceneMgr::Instance()->Draw();


				CFPS::Instance()->FpsCntUp();

			}
		}

	}


}

void CGameWnd::Release(HINSTANCE hInstance)
{
	::timeEndPeriod(1);				// タイマの分解能を元に戻す
	
	CDebug::Instance()->Release();

	CInput::Fin();
	fps->Release();

	//CObjManager::Instance()->Release();

	CSceneMgr::Instance()->Release();

	window->ReleaseWin(hInstance);

	/*scene = NULL;;
	objmgr = NULL;
	window = NULL;*/
}