#pragma once
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include"Window.h"
#include<d3dx9.h>

//=============================================================================
// ���C�u�����̃����N
//=============================================================================
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")

//=============================================================================
// class��`
//=============================================================================

class CDxDevice
{
private:
	LPDIRECT3D9 D3D;				// Directx3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 D3DDevice;	// �f�o�C�X�I�u�W�F�N�g
	D3DPRESENT_PARAMETERS D3DPP;	// ��ʏ��̐ݒ�

public:
	
	CDxDevice();
	~CDxDevice();

	// Directx��singleton
	static CDxDevice* Instance() {
		static CDxDevice _Instance;
		return &_Instance;
	}

	// Graphic�f�o�C�X�̃Q�b�^�[
	const LPDIRECT3DDEVICE9 GetDxDevice() { return D3DDevice; }

	// �f�o�C�X�̏����ݒ�
	bool CreateDxDevice();

};

//=============================================================================
// �f�o�C�X�Ăяo���p
//=============================================================================
inline CDxDevice* GetDxMgr()
{
	return CDxDevice::Instance();
}

