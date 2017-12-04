#include"includeheader.h"

/// <summary>
/// 2017/10/01@»ìŠJn
/// </summary>
/// <param name="hinstace"></param>
/// <param name="hPrevInstance"></param>
/// <param name="lpCmdLine"></param>
/// <param name="nCmdShow"></param>
/// <returns></returns>
int WINAPI WinMain(HINSTANCE hinstace,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{


	CWindowCreate::Getintance().InitWindow(hinstace, hPrevInstance, lpCmdLine, nCmdShow);

	CGameLoop* _gameLoop = new CGameLoop();

	_gameLoop->Init();

	_gameLoop->Run();

	_gameLoop->Release();

	delete _gameLoop;

	CWindowCreate::Getintance().ReleaseWindow();

	return 0;

}