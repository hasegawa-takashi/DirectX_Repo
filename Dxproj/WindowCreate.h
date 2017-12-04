#pragma once
#include"includeheader.h"


/// <summary>
/// �v���V�[�W���[����ǂ�����΂����̂��킩��Ȃ��̂�
/// �ÓI�ȃC���X�^���X���쐬����
/// </summary>
class CWindowCreate : public CSingleton<CWindowCreate>
{
public:
	CWindowCreate();
	~CWindowCreate();

	HRESULT InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);	// ��������
	void ReleaseWindow();	// �������

	//	-- �v���V�[�W���[����̐ݒ� -- //
	// �|�C���^�̐ݒ�
	void SetProcPointer(HWND hWnd);
	//	�v���V�[�W���[�̌Ăяo��
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	//	�v���V�[�W���[�̎���
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