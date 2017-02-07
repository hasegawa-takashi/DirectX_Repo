//
// DirectInput �N���X��`
//
#pragma once

#ifndef _INPUT_H_
#define _INPUT_H_

#include <windows.h>
#include <tchar.h>
#define DIRECTINPUT_VERSION 0x0800	// DirectX8 �𖾎�
#include <dinput.h>					// DirectInput �֘A�̃w�b�_

//-------- �L�[�{�[�h�֌W
#define MAX_KEY			256			// �L�[��

//-------- �W���C�X�e�B�b�N�֌W
#define JOY_X			0			// �w��
#define JOY_Y			1			// �x��

//-------- �}�E�X�֌W
#define MOUSE_X			0			// �w��
#define MOUSE_Y			1			// �x��
#define MOUSE_Z			2			// �y��

//-------- �Q�[���p�b�h�֌W
#define MAX_JOY			4			// �ő�F���ڑ���
#define JOY_MIN_X		-32768		// �w���ŏ��l
#define JOY_MAX_X		32767		// �w���ő�l
#define JOY_MIN_Y		-32768		// �x���ŏ��l
#define JOY_MAX_Y		32767		// �x���ő�l

class CInput
{
private:
	static LPDIRECTINPUT8		m_pDI;						// DirectInput8 �I�u�W�F�N�g
	static LPDIRECTINPUTDEVICE8	m_pDIDeviceKey;				// DirectInputDevice8 �I�u�W�F�N�g
	static BYTE					m_diKeyState[MAX_KEY];		// �L�[�{�[�h���擾�o�b�t�@
	static BYTE					m_diPrevKeyState[MAX_KEY];	// ���O�̃L�[�{�[�h���
	static LPDIRECTINPUTDEVICE8	m_pDIDeviceMouse;			// DirectInputDevice8 �I�u�W�F�N�g
	static DIMOUSESTATE			m_diMouseState;				// �}�E�X���擾�o�b�t�@
	static DIMOUSESTATE			m_diPrevMouseState;			// ���O�̃}�E�X���
	static LPDIRECTINPUTDEVICE8	m_pDIDeviceJoy[MAX_JOY];	// DirectInputDevice8 �I�u�W�F�N�g
	static DIJOYSTATE			m_diJoyState[MAX_JOY];		// �W���C�X�e�B�b�N���擾�o�b�t�@
	static DIJOYSTATE			m_diPrevJoyState[MAX_JOY];	// ���O�̃W���C�X�e�B�b�N���
	static int					m_nJoy;						// �W���C�X�e�B�b�N�ڑ���

	static BOOL CALLBACK		EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);

public:
	CInput(void);
	virtual ~CInput(void);

	static void Init(HWND hWnd);
	static void Fin(void);
	static void Update(void);

	static bool GetKeyPress(int nKey);
	static bool GetKeyTrigger(int nKey);
	static bool GetKeyRelease(int nKey);
	static int GetNumJoystick(void);
	static bool GetJoyPress(int nJoy, int nButton);
	static bool GetJoyTrigger(int nJoy, int nButton);
	static bool GetJoyRelease(int nJoy, int nButton);
	static float GetJoyAxis(int nJoy, int nAxis);
	static bool GetMousePress(int nButton);
	static bool GetMouseTrigger(int nButton);
	static bool GetMouseRelease(int nButton);
	static long GetMouseAxis(int nAxis);
};

#endif