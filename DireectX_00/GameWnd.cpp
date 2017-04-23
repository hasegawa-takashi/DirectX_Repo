//=============================================================================
// �C���N���[�h
//=============================================================================
#include "GameWnd.h"

//=============================================================================
// Define
//=============================================================================

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���錾
//=============================================================================

//=============================================================================
// �Q�[���̏�����
//=============================================================================
bool CGameWnd::Init(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int iCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_CrtSetBreakAlloc(1014);
	
	// �ϐ��錾
	HRESULT Createflag = E_FAIL;
	FpsCnt = 0;

	try
	{
		// �^�C�}�̕���\���Z�b�g
		timeBeginPeriod(1);

		// �E�C���h�E�̍쐬
		Createflag = GetWinMgr()->MakeWin(hInstance, hPrevInst, lpCmdLine, iCmdShow);
		if (Createflag == E_FAIL) { GetWinMgr()->MessageBox(_T("Win�̍쐬���s")); return false; }

		// DirectxDevice�̐ݒ�
		GetDxMgr()->CreateDxDevice();

		// Directx�̕`�����̐ݒ�
		GetRenderMgr()->Init();

		// Dxinput�̐ݒ�
		CInput::Init(GetWinMgr()->GethwndDevice());

		// �C���X�^���X�̏�����
		GetSceneMgr()->Init();

		// ��ԍŏ��̃^�C�g���̃v�b�V��
		GetSceneMgr()->PushScene<CTitle>();
		GetSceneMgr()->ChangeScene();

		// Obj�}�l�[�W���[�̏�����
		GetObjMgr()->Init();

		// �`��p�}�l�[�W���[�̏�����
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
// �Q�[���̋N��
//=============================================================================
void CGameWnd::Run()
{

	// �Q�[�����C�����[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
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


			// ������Scene/Obj�̍폜����
			GetObjMgr()->ObjMigration();
			GetSceneMgr()->Scenemigration();

		}

	}


}

//=============================================================================
// �I������
//=============================================================================
void CGameWnd::Release(HINSTANCE hInstance)
{
	::timeEndPeriod(1);				// �^�C�}�̕���\�����ɖ߂�
	
	CDebug::Instance()->Release();
	CInput::Fin();
	CFPS::Instance()->Release();
	CSceneMgr::Instance()->Release();
	GetWinMgr()->ReleaseWin(hInstance);

}