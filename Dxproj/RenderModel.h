#pragma once

#include"MyHierarchy.h"
#include"includeheader.h"

class CRenderModel
{
private:
	bool Init(LPCTSTR ModelName);
	void Release();

	bool IntersectFrame(LPD3DXFRAME pFrameBase,
		D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay,
		D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal);
	bool IntersectMeshContainer(
		LPD3DXMESHCONTAINER pMeshContainer,
		D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay,
		D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal);

	LPD3DXFRAME					m_FrameRoot;	// ルート フレーム オブジェクト
	LPD3DXANIMATIONCONTROLLER	m_AnimCtrl;	// アニメーション コントローラ オブジェクト
	UINT						m_NumAnimSet;	// アニメーション セット数
	LPD3DXANIMATIONSET*			m_AnimSet;	// アニメーション セット
	CMyHierarchy				m_Hierarchy;	// 階層メモリ確保/解放クラス
	DWORD						m_Prev;		// 直前の時刻
	bool						m_AnimationFlag;
public:
	CRenderModel(LPCTSTR ModelName);
	~CRenderModel();

	void AnimationUpdate(D3DXMATRIX& world);
	void RenderModel();
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	void DrawFrame(LPD3DXFRAME pFrame);
	void RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase);
	HRESULT AllocBoneMatrix(LPD3DXMESHCONTAINER pMeshContainerBase);
	HRESULT AllocAllBoneMatrix(LPD3DXFRAME pFrameBase);
	void SwitchAnimSet(UINT uAnimSet);
	void SetTime(double dTime);
	D3DXMATRIX* SerchBorn(LPSTR BornName);
	D3DXMATRIX* GetBorn(LPD3DXFRAME pFrameBase, LPSTR BornName);

	bool Intersect(D3DXVECTOR3& L0,
		D3DXVECTOR3& L1,
		bool bRay = false,
		D3DXVECTOR3* pCross = NULL,
		D3DXVECTOR3* pNormal = NULL);

};