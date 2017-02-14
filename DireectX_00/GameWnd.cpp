//=============================================================================
// �C���N���[�h
//=============================================================================
#include "GameWnd.h"
#include<tchar.h>
#include"Title.h"
#include"Sprite.h"
#include"mleak.h"

//=============================================================================
// Define
//=============================================================================
#define FRAME_RATE		(1000/60)	// �t���[�����[�g

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
	//_CrtSetBreakAlloc(193);
	
	// �ϐ��錾
	HRESULT Createflag = E_FAIL;
	FpsCnt = 0;

	// �C���X�^���X�̑O�u��
	window = CWindow::Instance();
	// �E�C���h�E�̍쐬��D3D�f�o�C�X�̏�����
	Createflag = window->MakeWin(hInstance, hPrevInst, lpCmdLine, iCmdShow);
	if (Createflag == E_FAIL)return false;

	CInput::Init(window->GethwndDevice());

	// ���̓R���e�L�X�g���w�肳�ꂽ�E�B���h�E�Ɋ֘A�t���܂�
	//::ImmAssociateContext(window->GethwndDevice(), NULL);
	
	// Window�̃X�N���[�����[�h�̐ݒ�(���͏o���Ȃ������̖؋�ł�)
	
	// �^�C�}�̕���\���Z�b�g
	timeBeginPeriod(1);

	// �C���X�^���X�̏�����
	CSceneMgr::Instance()->Init();

	// ��ԍŏ��̃^�C�g���̃v�b�V��
	CSceneMgr::Instance()->PushScene(new CTitle);

	// Obj�}�l�[�W���[�̏�����
	CObjManager::Instance()->Init();

	// �`��p�}�l�[�W���[�̏�����
	CFPS::Instance()->Init();

	CDebug::Instance()->Init();

	return true;

}

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
				CSceneMgr::Instance()->Update();
				CInput::Update();
				CSceneMgr::Instance()->Draw();


				CFPS::Instance()->FpsCntUp();

			}
		}

	}


}

void CGameWnd::Release(HINSTANCE hInstance)
{
	::timeEndPeriod(1);				// �^�C�}�̕���\�����ɖ߂�
	
	CDebug::Instance()->Release();

	CInput::Fin();
	fps->Release();

	//CObjManager::Instance()->Release();

	CSceneMgr::Instance()->Release();

	window->ReleaseWin(hInstance);

	/*scene = NULL;;
	objmgr = NULL;
	window = NULL;*/
}