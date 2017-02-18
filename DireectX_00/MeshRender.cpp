#include "MeshRender.h"
#include<tchar.h>
#include<string>

#pragma warning(disable:4996)


CMeshRender::CMeshRender()
{

	m_pFrameRoot = NULL;
	m_pAnimCtrl = NULL;
	m_uNumAnimSet = 0;
	m_ppAnimSet = NULL;
}


CMeshRender::~CMeshRender()
{
}

////////////////////////////////////////////////////////////////////////
//
//		メッシュを初期化するよ
//
////////////////////////////////////////////////////////////////////////
bool CMeshRender::Initialize(LPCTSTR pszFName)
{
	// ディレクトリ抽出
	TCHAR szDir[_MAX_PATH];
	TCHAR szDirWk[_MAX_DIR];
	_tsplitpath(pszFName, szDir, szDirWk, NULL, NULL);
	lstrcat(szDir, szDirWk);
	m_Hierarchy.SetDirectory(szDir);

	// 階層構造メッシュの読み込み
	// 3Dモデルの読み込み
	HRESULT hr = D3DXLoadMeshHierarchyFromX(pszFName,
		D3DXMESH_MANAGED, CWindow::Instance()->GetDevice(),
		&m_Hierarchy, NULL,
		&m_pFrameRoot, &m_pAnimCtrl);
	if (FAILED(hr)) 
		return false;

	// ボーンとフレームの関連付け
	hr = AllocAllBoneMatrix(m_pFrameRoot);
	if (FAILED(hr)) return false;

	// アニメーションセット取得
	m_uNumAnimSet = 0;
	if (m_pAnimCtrl) {
		m_uNumAnimSet = m_pAnimCtrl->GetNumAnimationSets();
		if (m_uNumAnimSet > 0) {
			m_ppAnimSet = new LPD3DXANIMATIONSET[m_uNumAnimSet];
			for (DWORD u = 0; u < m_uNumAnimSet; ++u) {
				m_pAnimCtrl->GetAnimationSet(u, &m_ppAnimSet[u]);
			}
		}
	}

	// 経過時間計測用時刻設定
	m_dwPrev = ::timeGetTime();

	return SUCCEEDED(hr);
}

////////////////////////////////////////////////////////////////////////
//
//		メッシュを開放するよ
//
////////////////////////////////////////////////////////////////////////
void CMeshRender::Finalize()
{
	// アニメーション破棄
	if (m_ppAnimSet) {
		for (DWORD u = 0; u < m_uNumAnimSet; ++u) {
			SAFE_RELEASE(m_ppAnimSet[u]);
		}
		SAFE_DELETE_ARRAY(m_ppAnimSet);
	}
	SAFE_RELEASE(m_pAnimCtrl);

	// メッシュ破棄
	if (m_pFrameRoot) {
		D3DXFrameDestroy(m_pFrameRoot, &m_Hierarchy);
		m_pFrameRoot = NULL;
	}
}

////////////////////////////////////////////////////////////////////////
//
//		アニメーション更新
//
////////////////////////////////////////////////////////////////////////
void CMeshRender::Update(D3DXMATRIX& world)
{
	// アニメーションの更新
	if (m_pAnimCtrl)
	{
		DWORD dwNow = ::timeGetTime();
		double d = (dwNow - m_dwPrev) / 1000.0;
		m_dwPrev = dwNow;
		m_pAnimCtrl->AdvanceTime(d, NULL);
	}
	// マトリックスの更新
	CWindow::Instance()->GetDevice()->SetTransform(D3DTS_WORLD, &world);
	if (m_pFrameRoot)
	{
		UpdateFrameMatrices(m_pFrameRoot, &world);
	}

}


////////////////////////////////////////////////////////////////////////
//
//		ついにメッシュ描画
//
////////////////////////////////////////////////////////////////////////
void CMeshRender::Render()
{
	if (m_pFrameRoot)
	{
		// フレーム描画
		DrawFrame(m_pFrameRoot);
	}
}

//---------------------------------------------------------------------------------------
// フレームのマトリックスを更新
//---------------------------------------------------------------------------------------
void CMeshRender::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	
	// 親のマトリックスを掛け合わせる
	if (pParentMatrix) {
		pFrame->CombinedTransformationMatrix =
			pFrame->TransformationMatrix * *pParentMatrix;
	}
	else {
		pFrame->CombinedTransformationMatrix =
			pFrame->TransformationMatrix;
	}

	// 兄弟フレームがあればマトリックスを更新
	if (pFrame->pFrameSibling) {
		UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
	}

	// 子フレームがあればマトリックスを更新
	if (pFrame->pFrameFirstChild) {
		// 自分が親となるので、自分のマトリックスを渡す
		UpdateFrameMatrices(pFrame->pFrameFirstChild,
			&pFrame->CombinedTransformationMatrix);
	}
}


////////////////////////////////////////////////////////////////////////
//
//		フレームの描画
//
////////////////////////////////////////////////////////////////////////
void CMeshRender::DrawFrame(LPD3DXFRAME pFrame)
{
	LPD3DXMESHCONTAINER pMeshContainer = pFrame->pMeshContainer;

	while(pMeshContainer)
	{
		// メッシュコンテナの描画
		RenderMeshContainer(pMeshContainer,pFrame);
		// 次のメッシュコンテナ
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}

	// 兄弟フレームがあれば兄弟フレームの描画
	if (pFrame->pFrameSibling)
		DrawFrame(pFrame->pFrameSibling);
	// 個フレームがあれば子フレームを描画
	if (pFrame->pFrameFirstChild)
		DrawFrame(pFrame->pFrameFirstChild);

}

/////////////////////////////////////////////////////////////////////////
//																	   //
//		メッシュコンテナの描画										   //
//																	   //
/////////////////////////////////////////////////////////////////////////
void CMeshRender::RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase , LPD3DXFRAME pFrameBase)
{
	// 入れ込み
	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;

	if (pMeshContainer->pSkinInfo)
	{
		// スキンメッシュモデル

		// ボーン情報
		LPD3DXBONECOMBINATION pBoneCombi = (LPD3DXBONECOMBINATION)pMeshContainer->pBoneBuffer->GetBufferPointer();

		// 
		DWORD dwPrevBoneID = UINT_MAX;
		DWORD dwBlendMatrix;

		for (DWORD i = 0; i < pMeshContainer->dwBone ; ++i)
		{
			dwBlendMatrix = 0;

			for (DWORD k = 0; k < pMeshContainer->dwBone; ++k)
			{
				try
				{
 					if (pBoneCombi[i].BoneId[k] != UINT_MAX)
						dwBlendMatrix = k;
				}
				catch (const std::exception&)
				{
					break;
				}
				
			}

			CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_VERTEXBLEND, dwBlendMatrix);
			for (DWORD k = 0; k < pMeshContainer->dwWeight; ++k)
			{
				DWORD id = pBoneCombi[i].BoneId[k];
				if (id != UINT_MAX)
				{
					CWindow::Instance()->GetDevice()->SetTransform(D3DTS_WORLDMATRIX(k), &(pMeshContainer->pBoneOffsetMatrix[id] * *pMeshContainer->ppBoneMatrix[id]));
				}
			}
			CWindow::Instance()->GetDevice()->SetMaterial(&pMeshContainer->pMaterials[pBoneCombi[i].AttribId].MatD3D);
			CWindow::Instance()->GetDevice()->SetTexture(0, pMeshContainer->ppTextures[pBoneCombi[i].AttribId]);
			dwPrevBoneID = pBoneCombi[i].AttribId;
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}
		// スキン情報のあるモデルの描画完了
		return;
	}

	// スキンなしモデル
	CWindow::Instance()->GetDevice()->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);
	for (DWORD iAttrib = 0; iAttrib < pMeshContainer->NumMaterials; ++iAttrib) {
		DWORD dwAttrib = pMeshContainer->pAttributeTable[iAttrib].AttribId;
		CWindow::Instance()->GetDevice()->SetMaterial(&pMeshContainer->pMaterials[dwAttrib].MatD3D);
		CWindow::Instance()->GetDevice()->SetTexture(0, pMeshContainer->ppTextures[dwAttrib]);
		pMeshContainer->MeshData.pMesh->DrawSubset(dwAttrib);
	}

}

/////////////////////////////////////////////////////////////////////////
//
//		ボーン用のワールドマトリクス領域確保
//
/////////////////////////////////////////////////////////////////////////
HRESULT CMeshRender::AllocBoneMatrix(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	if (pMeshContainer->pSkinInfo == NULL)
		return S_OK;	// スキン情報が無ければ何もしない
	DWORD dwBoneNum = pMeshContainer->pSkinInfo->GetNumBones();
	pMeshContainer->ppBoneMatrix = new LPD3DXMATRIX[dwBoneNum];
	for (DWORD i = 0; i < dwBoneNum; ++i) {
		MYFRAME* pFrame = (MYFRAME*)D3DXFrameFind(m_pFrameRoot,
			pMeshContainer->pSkinInfo->GetBoneName(i));
		if (pFrame == NULL)
			return E_FAIL;
		pMeshContainer->ppBoneMatrix[i] =
			&pFrame->CombinedTransformationMatrix;
	}
	return S_OK;
}

HRESULT CMeshRender::AllocAllBoneMatrix(LPD3DXFRAME pFrameBase)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	HRESULT hr = S_OK;
	if (pFrame->pMeshContainer) {
		hr = AllocBoneMatrix(pFrame->pMeshContainer);
		if (FAILED(hr))
			return hr;
	}
	if (pFrame->pFrameSibling) {
		hr = AllocAllBoneMatrix(pFrame->pFrameSibling);
		if (FAILED(hr))
			return hr;
	}
	if (pFrame->pFrameFirstChild) {
		hr = AllocAllBoneMatrix(pFrame->pFrameFirstChild);
	}
	return hr;
}

/////////////////////////////////////////////////////////////////////////
//
//		アニメーションの切り替え
//
/////////////////////////////////////////////////////////////////////////
void CMeshRender::SwitchAnimSet(UINT uAnimSet)
{
	if (uAnimSet >= m_uNumAnimSet || m_pAnimCtrl == NULL) 
		return;
	m_pAnimCtrl->SetTrackAnimationSet(0, m_ppAnimSet[uAnimSet]);
}


/////////////////////////////////////////////////////////////////////////
//
//		アニメーションの開始時間設定
//
/////////////////////////////////////////////////////////////////////////
void CMeshRender::SetTime(double dTime)
{
	if (m_pAnimCtrl == NULL)
		return;

	for (DWORD i = 0; i < m_pAnimCtrl->GetMaxNumTracks(); ++i)
	{
		m_pAnimCtrl->SetTrackPosition(i,0);
	}
	m_pAnimCtrl->ResetTime();
	m_pAnimCtrl->AdvanceTime(dTime, NULL);

}

/////////////////////////////////////////////////////////////////////////
//
//		対象物（坂とか）の角度の取得と計算？
//
/////////////////////////////////////////////////////////////////////////
bool CMeshRender::Intersect(D3DXVECTOR3& L0,
	D3DXVECTOR3& L1, bool bRay,
	D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal)
{
	// 線分の方向ベクトルを求める
	D3DXVECTOR3 W;
	if (bRay) {
		W = L1;
	}
	else {
		W = L1 - L0;
	}
	return IntersectFrame(m_pFrameRoot, L0, W, bRay, pCross, pNormal);
}

/////////////////////////////////////////////////////////////////////////
//
//		上の計算結果から結果の返信？
//
/////////////////////////////////////////////////////////////////////////
bool CMeshRender::IntersectFrame(LPD3DXFRAME pFrameBase,
	D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay,
	D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	bool bResult = false;

	if (!pFrame)
		return bResult;

	if (pFrame->pMeshContainer) {
		bResult = IntersectMeshContainer(pFrame->pMeshContainer,
			L0, W, bRay, pCross, pNormal);
		if (bResult)
			return bResult;
	}
	if (pFrame->pFrameSibling) {
		bResult = IntersectFrame(pFrame->pFrameSibling,
			L0, W, bRay, pCross, pNormal);
		if (bResult)
			return bResult;
	}
	if (pFrame->pFrameFirstChild) {
		bResult = IntersectFrame(pFrame->pFrameFirstChild,
			L0, W, bRay, pCross, pNormal);
	}
	return bResult;
}

/////////////////////////////////////////////////////////////////////////
//
//		メッシュコンテナの内部メッシュを見て
//		角度を計算して返してるっぽい？
//		アニメーションにおける角度制限？
//
/////////////////////////////////////////////////////////////////////////
bool CMeshRender::IntersectMeshContainer(
	LPD3DXMESHCONTAINER pMeshContainer,
	D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay,
	D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal)
{
	bool bResult = false;

	LPD3DXMESH pMesh = pMeshContainer->MeshData.pMesh;
	LPBYTE pVtx;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pVtx);
	WORD* pIdx;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pIdx);
	DWORD dwStride = pMesh->GetNumBytesPerVertex();
	DWORD dwIdx = pMesh->GetNumFaces();
	for (DWORD i = 0; i < dwIdx; ++i) {
		// 三角形の頂点取得
		D3DXVECTOR3 P0 = *(LPD3DXVECTOR3)(pVtx + dwStride * *pIdx++);
		D3DXVECTOR3 P1 = *(LPD3DXVECTOR3)(pVtx + dwStride * *pIdx++);
		D3DXVECTOR3 P2 = *(LPD3DXVECTOR3)(pVtx + dwStride * *pIdx++);
		// 三角形の辺のベクトル取得
		D3DXVECTOR3 P0P1 = P1 - P0;
		D3DXVECTOR3 P1P2 = P2 - P1;
		D3DXVECTOR3 P2P0 = P0 - P2;
		// 三角形の辺と線分の作る面の法線ベクトル取得
		D3DXVECTOR3 N;
		D3DXVec3Cross(&N, &P0P1, &W);
		if (D3DXVec3Dot(&N, &(L0 - P0)) < 0.0f) {
			continue;
		}
		D3DXVec3Cross(&N, &P1P2, &W);
		if (D3DXVec3Dot(&N, &(L0 - P1)) < 0.0f) {
			continue;
		}
		D3DXVec3Cross(&N, &P2P0, &W);
		if (D3DXVec3Dot(&N, &(L0 - P2)) < 0.0f) {
			continue;
		}
		// 三角形の法線ベクトル取得、正規化
		D3DXVec3Cross(&N, &P0P1, &P1P2);
		D3DXVec3Normalize(&N, &N);
		// 媒介変数tを求める前の分母を計算
		float base = D3DXVec3Dot(&N, &W);
		if (base == 0.0f) {
			continue;	// 線分と面が平行
		}
		// tを求める
		float t = D3DXVec3Dot(&N, &(P0 - L0)) / base;
		if (t < 0.0f) {
			continue;	// 交点が始点より後方
		}
		if (!bRay && t > 1.0f) {
			continue;	// 交点が終点より前方
		}
		// 交点を求める
		if (pCross) {
			*pCross = L0 + t * W;
		}
		// 法線ベクトルを返す
		if (pNormal) {
			*pNormal = N;
		}
		// 交点がみつかった
		bResult = true;
		break;
	}
	pMesh->UnlockIndexBuffer();
	pMesh->UnlockVertexBuffer();

	return bResult;
}

/////////////////////////////////////////////////////////////////////////
//
//		ボーンの探索
//
/////////////////////////////////////////////////////////////////////////
D3DXMATRIX* CMeshRender::SerchBorn( LPSTR BornName)
{
	return GetBorn(m_pFrameRoot,BornName);
}

D3DXMATRIX* CMeshRender::GetBorn(LPD3DXFRAME pFrameBase ,LPSTR BornName)
{
	//LPD3DXMESHCONTAINER pMeshContainerBase = m_pFrameRoot->pMeshContainer;

	if (std::string(pFrameBase->Name).compare(BornName) == 0)
	{
		MYFRAME* pFrame = (MYFRAME*)pFrameBase;
		return &pFrame->CombinedTransformationMatrix;
	}

	if (pFrameBase->pFrameFirstChild)
		GetBorn(pFrameBase->pFrameFirstChild, BornName);
	else
		return NULL;


	return NULL;
}

/////////////////////////////////////////////////////////////////////////
//
//		おわり
//
/////////////////////////////////////////////////////////////////////////