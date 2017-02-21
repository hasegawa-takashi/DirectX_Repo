//=============================================================================
//
// window���� [window.h]
//
//=============================================================================
#ifndef _WINDOW_H_
#define _WINDOW_H_

//=============================================================================
//	�C���N���[�h
//=============================================================================
#include<Windows.h>
#include<tchar.h>
#include"DxDevice.h"

//=============================================================================
// ���C�u�����̃����N
//=============================================================================
#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")
#endif

//=============================================================================
// �}�N����`
//=============================================================================
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)
#define FOVY			45.0f					// ����p
#define NEAR_CLIP		1.0f					// �j�A�N���b�v���s������
#define FAR_CLIP		10000.0f				// �t�@�[�N���b�v���s������


//=============================================================================
// class��`
//=============================================================================

class CWindow{

private:
	HWND hWnd;
	MSG  msg;

	bool bWinmode;						//�t���X�N���[��or�E�C���h�E�Y

	int							m_nWidth;		// �\���̈敝
	int							m_nHeight;		// �\���̈捂��

	CWindow* cWnd;
	CWindow(){};

public:

	// Window��Singleton
	static CWindow* Instance(){
		static CWindow _WindowInstance;
		return &_WindowInstance;
	}

	// �O���t�B�b�N�f�o�C�X�̃Q�b�^�[
	const HWND GethwndDevice() { return hWnd; }
	const bool GetWindowMode() { return bWinmode; }

	//	Window�̍쐬
	HRESULT MakeWin(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

	//	�E�C���h�E�̉��
	void ReleaseWin(HINSTANCE);

	int MessageBox(LPCTSTR pszText, LPCTSTR pszCaption = NULL, UINT nType = MB_OK);

	//	-- �v���V�[�W���[����̐ݒ� -- //
	// �|�C���^�̐ݒ�
	void SetProcPointer(HWND hWnd);
	//	�v���V�[�W���[�̌Ăяo��
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	//	�v���V�[�W���[�̎���
	virtual LRESULT MainProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// �f�B�X�g���N�^�E�R���X�g���N�^
	~CWindow(){};

protected:

};

//=============================================================================
// �f�o�C�X�Ăяo���p
//=============================================================================
inline CWindow* GetWinMgr()
{
	return CWindow::Instance();
}



#endif