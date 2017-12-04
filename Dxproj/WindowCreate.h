#pragma once
#include"includeheader.h"


/// <summary>
/// プロシージャー周りどうすればいいのかわからないので
/// 静的なインスタンスを作成した
/// </summary>
class CWindowCreate : public CSingleton<CWindowCreate>
{
public:
	CWindowCreate();
	~CWindowCreate();

	HRESULT InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);	// 初期処理
	void ReleaseWindow();	// 解放処理

	//	-- プロシージャー周りの設定 -- //
	// ポインタの設定
	void SetProcPointer(HWND hWnd);
	//	プロシージャーの呼び出し
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	//	プロシージャーの実装
	virtual LRESULT MainProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	const HWND GethwndDevice() { return m_hWnd; }
	const bool GetWindowMode() { return m_Winmode; }

	char* GetCLASSNAME() { return CLASS_NAME; }
	char* GetWINDOWNAME() { return WINDOW_NAME; }

	int GetSCREENWIDTH() { return SCREEN_WIDTH; }
	int GetSCREENHEIGHT() { return SCREEN_HEIGHT; }
	int GetASPECT() { return ASPECT; }

private:

	HWND m_hWnd;
	MSG m_Message;
	HINSTANCE m_hInstance;
	bool m_Winmode;

	int SCREEN_WIDTH = 800;
	int SCREEN_HEIGHT = 600;
	int ASPECT = SCREEN_WIDTH / SCREEN_HEIGHT;

	char* CLASS_NAME = "DirectxProj";
	char* WINDOW_NAME = "DirectxProj";

};