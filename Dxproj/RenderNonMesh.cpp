#include "RenderNonMesh.h"



CRenderNonMesh::CRenderNonMesh(LPCTSTR ModelName)
{
	m_MatBuf = nullptr;
	m_Mesh = nullptr;
	m_Mat = 0;
	m_MeshMat = nullptr;
	m_MeshTex = nullptr;

	TCHAR _Dir[_MAX_PATH];
	TCHAR _DirWk[_MAX_DIR];
	_tsplitpath(ModelName, _Dir, _DirWk, NULL, NULL);
	lstrcat(_Dir, _DirWk);

	if(D3D_OK != D3DXLoadMeshFromX(ModelName,D3DXMESH_SYSTEMMEM,CDirectxMgr::Getintance().GetDxDevice(),NULL,&m_MatBuf,NULL,&m_Mat,&m_Mesh))
	{
		return;
	}

	if (m_Mesh->GetFVF()&D3DFVF_NORMAL)
	{
		LPD3DXMESH meshtmp = m_Mesh;
		meshtmp->CloneMeshFVF(meshtmp->GetOptions(),meshtmp->GetFVF() | D3DFVF_NORMAL, CDirectxMgr::Getintance().GetDxDevice(),&m_Mesh);
		meshtmp->Release();
		D3DXComputeNormals(m_Mesh,NULL);
	}

	D3DXMATERIAL*	d3Mat = (D3DXMATERIAL*)m_MatBuf->GetBufferPointer();
	m_MeshMat = new D3DMATERIAL9[m_Mat];		// ���b�V�������m��
	m_MeshTex = new LPDIRECT3DTEXTURE9[m_Mat];// �e�N�X�`�����m��

	DWORD			i;
	for (i = 0; i < m_Mat; i++)
	{
		m_MeshMat[i] = d3Mat[i].MatD3D;			// �}�e���A�����Z�b�g
		m_MeshMat[i].Ambient = m_MeshMat[i].Diffuse;// ����������
		m_MeshTex[i] = NULL;	// �e�N�X�`��������

							// �g�p���Ă���e�N�X�`��������Γǂݍ���
		if (d3Mat[i].pTextureFilename != NULL &&
			lstrlen(d3Mat[i].pTextureFilename) > 0)
		{
			// �e�N�X�`���ǂݍ���
			D3DXCreateTextureFromFile(
				CDirectxMgr::Getintance().GetDxDevice(),
				d3Mat[i].pTextureFilename,
				&m_MeshTex[i]);
		}
	}

	m_MatBuf->Release();

}



CRenderNonMesh::~CRenderNonMesh()
{
	DWORD	i;
	// �e�N�X�`���J��
	for (i = 0; i < m_Mat; i++)
	{
		m_MeshTex[i]->Release();
		m_MeshTex[i] = NULL;
	}
	delete[] m_MeshTex;
	m_MeshTex = NULL;
	delete[] m_MeshMat;
	m_MeshMat = NULL;
}

void CRenderNonMesh::Render()
{
	DWORD	i;
	for (i = 0; i < m_Mat; i++)
	{
		CDirectxMgr::Getintance().GetDxDevice()->SetMaterial(&m_MeshMat[i]);	// �}�e���A�������Z�b�g
		CDirectxMgr::Getintance().GetDxDevice()->SetTexture(0, m_MeshTex[i]);	// �e�N�X�`�������Z�b�g
		m_Mesh->DrawSubset(i);				// ���b�V����`��
	}
}

void CRenderNonMesh::SetPos()
{

}