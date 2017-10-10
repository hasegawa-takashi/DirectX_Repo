#include "GameLoop.h"

CGameLoop::CGameLoop()
{

	timeBeginPeriod(1);

	// メモリーリークdebug用
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_CrtSetBreakAlloc(212);

}


CGameLoop::~CGameLoop()
{
}

void CGameLoop::Init()
{
	timeBeginPeriod(1);	// 分解能のセット

	CDirectxMgr::Getintance().CreateDxDevice();
	CRenderFormat::Getintance().Init();
	CInput::Init(CWindowCreate::Getintance().GethwndDevice());
	CCamera::Getintance().Init();

	CSceneMgr::Getintance().PushScene<CGameScene>();
	CSceneMgr::Getintance().ChangeScene();

	CSceneMgr::Getintance().Init();

}

void CGameLoop::Reboot()
{

}

void CGameLoop::Run()
{
	while (1)
	{
		if (PeekMessage(&m_Message, NULL, 0, 0, PM_REMOVE))
		{
			if (m_Message.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&m_Message);
				DispatchMessage(&m_Message);
			}
		}

		CGameFps::Getintance().Update();

		if (CGameFps::Getintance().GetUpdatetiming() == true)
		{
			CSceneMgr::Getintance().Init();
			CSceneMgr::Getintance().Update();
			CInput::Update();
			CSceneMgr::Getintance().Draw();
		}
		
		CObjMgr::Getintance().ObjMigration();
		CSceneMgr::Getintance().SceneMigration();
	}

}

void CGameLoop::Release()
{
	::timeEndPeriod(1);

	CSceneMgr::Getintance().Release();
	CInput::Fin();
	CSceneMgr::Getintance().Release();
	
}