#include "GameLoop.h"

CGameLoop::CGameLoop()
{

	timeBeginPeriod(1);

	// �������[���[�Ndebug�p
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_CrtSetBreakAlloc(598);

}


CGameLoop::~CGameLoop()
{
}

void CGameLoop::Init()
{
	timeBeginPeriod(1);	// ����\�̃Z�b�g
	srand((unsigned int)time(NULL));
	CDirectxMgr::Getintance().CreateDxDevice();
	CRenderFormat::Getintance().Init();
	CInput::Init(CWindowCreate::Getintance().GethwndDevice());
	CCamera::Getintance().Init();

	CSceneMgr::Getintance().PushScene<CTitleScene>();
	CSceneMgr::Getintance().ChangeScene();
}

void CGameLoop::Reboot()
{

}

void CGameLoop::Run()
{
	while (true)
	{
		if (PeekMessage(&m_Message, NULL, 0, 0, PM_REMOVE))
		{
			if (m_Message.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
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
		else
		{
			continue;
		}
		
		CObjMgr::Getintance().ObjMigration();
		CSceneMgr::Getintance().SceneMigration();
	}

}

void CGameLoop::Release()
{
	::timeEndPeriod(1);

	CObjMgr::Getintance().Release();
	CObjMgr::Getintance().ObjAllClear();
	CInput::Fin();
	CSceneMgr::Getintance().Release();
	CXAudioInterface::Instance()->ReleaseXAudio();	
}