#include "Window.h"

//=============================================================================
//
// Window����[Window.h]
//
//=============================================================================


#define CLASS_NAME  _T("DX22")	//�E�C���h�E�̃N���X��
#define WINDOW_NAME _T("DX22")	//�E�C���h�E�̃L���v�V������

//=============================================================================
// �C���N���[�h
//=============================================================================
#include"Window.h"

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���錾
//=============================================================================

//=============================================================================
//
//	�E�C���h�E�v���V�[�W���|�C���^
//	
//=============================================================================
void CWindow::SetProcPointer(HWND hWnd)
{
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)this);
}
//=============================================================================
//
//	�E�C���h�E�v���V�[�W���Ăяo��
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
//	�v���V�[�W���[���C������
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
//	�E�C���h�E�̐����{����������
//
//=============================================================================
HRESULT CWindow::MakeWin(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ϐ�������
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

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
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

	

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);



	return S_OK;

}

//=============================================================================
//
//	�I������
//
//=============================================================================
void CWindow::ReleaseWin(HINSTANCE hInstance )
{
	UnregisterClass(CLASS_NAME, hInstance);

	delete cWnd;
}

//=============================================================================
// ���b�Z�[�W �{�b�N�X�̕\��
//	in :	pszText		���b�Z�[�W �{�b�N�X�̃e�L�X�g�̃A�h���X
//			pszCaption	���b�Z�[�W �{�b�N�X�̃^�C�g���̃A�h���X
//			nType		���b�Z�[�W �{�b�N�X�̃X�^�C��
//	out:	�����ꂽ�{�^��
//=============================================================================
int CWindow::MessageBox(LPCTSTR pszText, LPCTSTR pszCaption, UINT nType)
{
	return ::MessageBox(hWnd, pszText, pszCaption, nType);
}