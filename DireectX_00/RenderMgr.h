#pragma once
//////////////////////////////////////////////////////////////
//
//		RenderManafer
//			�`��֐�
//
/////////////////////////////////////////////////////////////

//	�C���N���[�h
#include"Window.h"
#include"DxDevice.h"

#define	NUM_VERTEX		(4)		// ���_��
#define	NUM_POLYGON		(2)		// �|���S����

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

//////////////////////////////////////////////////////////////
//
//		CRenderMgr
//			�`��𓝊����邠��撣���č쐬��
//
/////////////////////////////////////////////////////////////
class CRenderMgr 
{

public:
	~CRenderMgr() {};

	CRenderMgr() {};
	//---------------------------------------
	// �I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X
	static CRenderMgr* Instance(void) {
		static CRenderMgr _instance;
		return &_instance;
	}

	//---------------------------------------
	// �`��̏�����
	void Init();
	
	//---------------------------------------
	// �`��O�̏���
	void  RenderTransStart();
	//---------------------------------------
	// �`��O�̏I��
	void  RenderEnd();

private:

	D3DXMATRIX	m_MatView;		// �r���[ �}�g���b�N�X
	D3DXMATRIX	m_MatProj;		// �ˉe�}�g���b�N�X

};

//=============================================================================
// �f�o�C�X�Ăяo���p
//=============================================================================
inline CRenderMgr* GetRenderMgr()
{
	return CRenderMgr::Instance();
}

//====================================================================================
//									EOF
//====================================================================================
