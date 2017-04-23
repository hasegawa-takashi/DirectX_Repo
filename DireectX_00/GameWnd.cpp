//=============================================================================
// インクルード
//=============================================================================
#include "GameWnd.h"

//=============================================================================
// Define
//=============================================================================

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
	//_CrtSetBreakAlloc(1014);
	
	// 変数宣言
	HRESULT Createflag = E_FAIL;
	FpsCnt = 0;

	try
	{
		// タイマの分解能をセット
		timeBeginPeriod(1);

		// ウインドウの作成
		Createflag = GetWinMgr()->MakeWin(hInstance, hPrevInst, lpCmdLine, iCmdShow);
		if (Createflag == E_FAIL) { GetWinMgr()->MessageBox(_T("Winの作成失敗")); return false; }

		// DirectxDeviceの設定
		GetDxMgr()->CreateDxDevice();

		// Directxの描画周りの設定
		GetRenderMgr()->Init();

		// Dxinputの設定
		CInput::Init(GetWinMgr()->GethwndDevice());

		// インスタンスの初期化
		GetSceneMgr()->Init();

		// 一番最初のタイトルのプッシュ
		GetSceneMgr()->PushScene<CTitle>();
		GetSceneMgr()->ChangeScene();

		// Objマネージャーの初期化
		GetObjMgr()->Init();

		// 描画用マネージャーの初期化
		CFPS::Instance()->Init();

		CDebug::Instance()->Init();
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}



}
//=============================================================================
// ゲームの起動
//=============================================================================
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
				GetSceneMgr()->Init();

				GetSceneMgr()->Update();
				CInput::Update();
				GetSceneMgr()->Draw();
				CFPS::Instance()->FpsCntUp();
			}


			// ここにScene/Objの削除処理
			GetObjMgr()->ObjMigration();
			GetSceneMgr()->Scenemigration();

		}

	}


}

//=============================================================================
// 終了処理
//=============================================================================
void CGameWnd::Release(HINSTANCE hInstance)
{
	::timeEndPeriod(1);				// タイマの分解能を元に戻す
	
	CDebug::Instance()->Release();
	CInput::Fin();
	CFPS::Instance()->Release();
	CSceneMgr::Instance()->Release();
	GetWinMgr()->ReleaseWin(hInstance);

}