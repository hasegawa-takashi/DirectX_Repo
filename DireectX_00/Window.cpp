#include "Window.h"

//=============================================================================
//
// Window処理[Window.h]
//
//=============================================================================


#define CLASS_NAME  _T("DX22")	//ウインドウのクラス名
#define WINDOW_NAME _T("DX22")	//ウインドウのキャプション名

//=============================================================================
// インクルード
//=============================================================================
#include"Window.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル宣言
//=============================================================================

//=============================================================================
//
//	ウインドウプロシージャポインタ
//	
//=============================================================================
void CWindow::SetProcPointer(HWND hWnd)
{
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)this);
}
//=============================================================================
//
//	ウインドウプロシージャ呼び出し
//	
//=============================================================================
LRESULT CALLBACK CWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CWindow* thisPtr = (CWindow*)GetWindowLong(hWnd, GWL_USERDATA);

	if (!thisPtr)
	{
		if (uMsg == WM_CREATE)
			thisPtr = (CWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;

		if (thisPtr)
		{
			thisPtr->SetProcPointer(hWnd);
		}

	}

	if (thisPtr)
	{
		LRESULT lResult = thisPtr->MainProc(hWnd, uMsg, wParam, lParam);
		return lResult;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//=============================================================================
//
//	プロシージャーメイン処理
//
//=============================================================================
LRESULT CWindow::MainProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
//
//	ウインドウの生成＋初期化処理
//
//=============================================================================
HRESULT CWindow::MakeWin(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 変数初期化
	bWinmode = TRUE;
	cWnd = new CWindow;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		CWindow::WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
		NULL,
		NULL,
		hInstance,
		(LPVOID)cWnd);

	

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);



	return S_OK;

}

//=============================================================================
//
//	終了処理
//
//=============================================================================
void CWindow::ReleaseWin(HINSTANCE hInstance )
{
	UnregisterClass(CLASS_NAME, hInstance);

	delete cWnd;
}

//=============================================================================
// メッセージ ボックスの表示
//	in :	pszText		メッセージ ボックスのテキストのアドレス
//			pszCaption	メッセージ ボックスのタイトルのアドレス
//			nType		メッセージ ボックスのスタイル
//	out:	押されたボタン
//=============================================================================
int CWindow::MessageBox(LPCTSTR pszText, LPCTSTR pszCaption, UINT nType)
{
	return ::MessageBox(hWnd, pszText, pszCaption, nType);
}