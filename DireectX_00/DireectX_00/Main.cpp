///////////////////////////////////////////////////////////////////////////////////////
//
//	メイン
//
///////////////////////////////////////////////////////////////////////////////////////


#include<Windows.h>
#include<tchar.h>
#include<stdlib.h>
#include"Window.h"
#include"GameWnd.h"

// ライブラリリンク
#pragma comment(lib, "winmm.lib")/*
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")*/

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int iCmdShow)
{
	bool Initflag;

	CGameWnd *gamewnd = CGameWnd::Instance();

	Initflag = gamewnd->Init(hInstance, hPrevInst, lpCmdLine, iCmdShow);

	if (!Initflag)return -1;

	// ココの内部で回してるよ
	gamewnd->Run();

	gamewnd->Release(hInstance);

	gamewnd = NULL;

	return -1;
}