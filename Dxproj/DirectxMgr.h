#pragma once

#include"includeheader.h"

class CDirectxMgr : public CSingleton<CDirectxMgr>
{
public:
	CDirectxMgr();
	~CDirectxMgr();

	
	// �f�o�C�X�̏����ݒ�
	bool CreateDxDevice();

	LPDIRECT3DDEVICE9 GetDxDevice() { return m_D3DDevice; }
private:
	LPDIRECT3D9 m_D3D9;				// Directx3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_D3DDevice;	// �f�o�C�X�I�u�W�F�N�g
	D3DPRESENT_PARAMETERS m_D3DPP;	// ��ʏ��̐ݒ�

};

