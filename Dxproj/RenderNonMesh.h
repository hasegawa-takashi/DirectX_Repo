#pragma once
#include"includeheader.h"

class CRenderNonMesh
{
public:
	CRenderNonMesh(LPCTSTR ModelName);
	~CRenderNonMesh();

	void Render();

private:
	LPD3DXBUFFER	m_MatBuf;
	LPD3DXMESH		m_Mesh;	// ���b�V���f�[�^
	DWORD			m_Mat;	// �}�e���A���̐�
	D3DMATERIAL9*	m_MeshMat;	// �}�e���A�����
	LPDIRECT3DTEXTURE9*	m_MeshTex;	// ���b�V���̃e�N�X�`��
};

