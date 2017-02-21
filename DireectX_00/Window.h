//=============================================================================
//
// window処理 [window.h]
//
//=============================================================================
#ifndef _WINDOW_H_
#define _WINDOW_H_

//=============================================================================
//	インクルード
//=============================================================================
#include<Windows.h>
#include<tchar.h>
#include"DxDevice.h"

//=============================================================================
// ライブラリのリンク
//=============================================================================
#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")
#endif

//=============================================================================
// マクロ定義
//=============================================================================
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)
#define FOVY			45.0f					// 視野角
#define NEAR_CLIP		1.0f					// ニアクリップを行う距離
#define FAR_CLIP		10000.0f				// ファークリップを行う距離


//=============================================================================
// class定義
//=============================================================================

class CWindow{

private:
	HWND hWnd;
	MSG  msg;

	bool bWinmode;						//フルスクリーンorウインドウズ

	int							m_nWidth;		// 表示領域幅
	int							m_nHeight;		// 表示領域高さ

	CWindow* cWnd;
	CWindow(){};

public:

	// WindowのSingleton
	static CWindow* Instance(){
		static CWindow _WindowInstance;
		return &_WindowInstance;
	}

	// グラフィックデバイスのゲッター
	const HWND GethwndDevice() { return hWnd; }
	const bool GetWindowMode() { return bWinmode; }

	//	Windowの作成
	HRESULT MakeWin(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

	//	ウインドウの解放
	void ReleaseWin(HINSTANCE);

	int MessageBox(LPCTSTR pszText, LPCTSTR pszCaption = NULL, UINT nType = MB_OK);

	//	-- プロシージャー周りの設定 -- //
	// ポインタの設定
	void SetProcPointer(HWND hWnd);
	//	プロシージャーの呼び出し
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	//	プロシージャーの実装
	virtual LRESULT MainProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// ディストラクタ・コンストラクタ
	~CWindow(){};

protected:

};

//=============================================================================
// デバイス呼び出し用
//=============================================================================
inline CWindow* GetWinMgr()
{
	return CWindow::Instance();
}



#endif