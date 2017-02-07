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
#include<d3dx9.h>
#include<tchar.h>

#define DIRECTINPUT_VERSION (0x0800)	//警告対処法

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

	LPDIRECT3D9			g_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9	g_pD3DDevice;	// デバイスオブジェクト(描画に必要)
	D3DPRESENT_PARAMETERS d3dpp;
	//LPD3DXFONT					m_pFont;		// D3DXFont オブジェクト

	D3DXMATRIX					m_MatView;		// ビュー マトリックス
	D3DXMATRIX					m_MatProj;		// 射影マトリックス

	HWND						m_hWnd;			// ウィンドウ ハンドル
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
	LPDIRECT3DDEVICE9 GetDevice(){ return g_pD3DDevice; }

	// グラフィックデバイスのゲッター
	HWND GethwndDevice(){return hWnd;}

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



#endif