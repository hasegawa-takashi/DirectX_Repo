#pragma once

#include "MyHierarchy.h"
#include"Window.h"
#include"RenderMgr.h"

class CMeshRender
{
private:
	LPD3DXFRAME					m_pFrameRoot;	// ルート フレーム オブジェクト
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;	// アニメーション コントローラ オブジェクト
	UINT						m_uNumAnimSet;	// アニメーション セット数
	LPD3DXANIMATIONSET*			m_ppAnimSet;	// アニメーション セット
	CMyHierarchy				m_Hierarchy;	// 階層メモリ確保/解放クラス
	DWORD						m_dwPrev;		// 直前の時刻

public:
	CMeshRender();
	~CMeshRender();

	bool Initialize(LPCTSTR pszFName);		// メッシュ初期化
	void Finalize();						// メッシュ解放
	void Update(D3DXMATRIX& world);			// メッシュ更新
	void Render();							// メッシュ描画
	void SwitchAnimSet(UINT uAnimSet);		// アニメーション切替
	void SetTime(double dTime);				// アニメーション開始時間設定

	bool Intersect(D3DXVECTOR3& L0,
		D3DXVECTOR3& L1,
		bool bRay = false,
		D3DXVECTOR3* pCross = NULL,
		D3DXVECTOR3* pNormal = NULL);


	D3DXMATRIX* SerchBorn(LPSTR BornName);

private:

	D3DXMATRIX* GetBorn(LPD3DXFRAME pFrameBase, LPSTR BornName);

	void RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase);
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	void DrawFrame(LPD3DXFRAME pFrame);
	HRESULT AllocBoneMatrix(LPD3DXMESHCONTAINER pMeshContainerBase);
	HRESULT AllocAllBoneMatrix(LPD3DXFRAME pFrameBase);

	bool IntersectFrame(LPD3DXFRAME pFrameBase,
		D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay,
		D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal);
	bool IntersectMeshContainer(
		LPD3DXMESHCONTAINER pMeshContainer,
		D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay,
		D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal);



};

