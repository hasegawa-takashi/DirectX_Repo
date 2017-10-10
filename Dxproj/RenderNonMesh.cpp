#include "RenderNonMesh.h"



CRenderNonMesh::CRenderNonMesh(LPCTSTR ModelName)
{

	HRESULT hr = (D3DXLoadMeshFromX(ModelName, D3DXMESH_MANAGED, CDirectxMgr::Getintance().GetDxDevice(), NULL, &m_MatBuf, NULL, &m_Mat, &m_Mesh));

	if (!hr)
	{
		return;
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
			hr = D3DXCreateTextureFromFile(
				CDirectxMgr::Getintance().GetDxDevice(),
				d3Mat[i].pTextureFilename,
				&m_MeshTex[i]);

			if (!hr)
			{
				return;
			}

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