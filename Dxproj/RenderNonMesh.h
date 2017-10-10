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
	LPD3DXMESH		m_Mesh;	// メッシュデータ
	DWORD			m_Mat;	// マテリアルの数
	D3DMATERIAL9*	m_MeshMat;	// マテリアル情報
	LPDIRECT3DTEXTURE9*	m_MeshTex;	// メッシュのテクスチャ
};

