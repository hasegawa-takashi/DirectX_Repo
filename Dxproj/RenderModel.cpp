#include "RenderModel.h"



CRenderModel::CRenderModel(LPCTSTR ModelName)
{
	Init(ModelName);
}


CRenderModel::~CRenderModel()
{
	Release();
}

bool CRenderModel::Init(LPCTSTR ModelName)
{
	TCHAR _Dir[_MAX_PATH];
	TCHAR _DirWk[_MAX_DIR];

	_tsplitpath(ModelName,_Dir,_DirWk,NULL,NULL);
	lstrcat(_Dir,_DirWk);

	m_Hierarchy.SetDirectory(_Dir);

	HRESULT hr = D3DXLoadMeshHierarchyFromX(ModelName,
		D3DXMESH_MANAGED,
		CDirectxMgr::Getintance().GetDxDevice(),
		&m_Hierarchy,
		NULL,
		&m_FrameRoot,
		&m_AnimCtrl);

	m_NumAnimSet = 0;
	if (m_AnimCtrl) {
		m_NumAnimSet = m_AnimCtrl->GetNumAnimationSets();
		if (m_NumAnimSet > 0) {
			m_AnimSet = new LPD3DXANIMATIONSET[m_NumAnimSet];
			for (DWORD u = 0; u < m_NumAnimSet; ++u) {
				m_AnimCtrl->GetAnimationSet(u, &m_AnimSet[u]);
			}
		}
	}
	// 経過時間計測用時刻設定
	m_Prev = ::timeGetTime();
	
	return SUCCEEDED(hr);
}

void CRenderModel::Release()
{
	// アニメーション破棄
	if (m_AnimSet) {
		for (DWORD u = 0; u < m_NumAnimSet; ++u) {
			Complete_type_safe_delete(m_AnimSet[u]);
		}
		Complete_type_safe_delete(m_AnimSet);
	}
	Complete_type_safe_delete(m_AnimCtrl);

	// メッシュ破棄
	if (m_FrameRoot) {
		D3DXFrameDestroy(m_FrameRoot, &m_Hierarchy);
		m_FrameRoot = NULL;
	}
}

void CRenderModel::AnimationUpdate(D3DXMATRIX& world)
{
	// アニメーションの更新
	if (m_AnimCtrl)
	{
		DWORD dwNow = ::timeGetTime();
		double d = (dwNow - m_Prev) / 1000.0;
		m_Prev = dwNow;
		m_AnimCtrl->AdvanceTime(d, NULL);
	}
	// マトリックスの更新
	CDirectxMgr::Getintance().GetDxDevice()->SetTransform(D3DTS_WORLD, &world);
	if (m_FrameRoot)
	{
		UpdateFrameMatrices(m_FrameRoot, &world);
	}

}

void CRenderModel::RenderModel()
{
	if (m_FrameRoot)
	{
		// フレーム描画
		DrawFrame(m_FrameRoot);
	}
}

void CRenderModel::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
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

void CRenderModel::DrawFrame(LPD3DXFRAME pFrame)
{
	LPD3DXMESHCONTAINER pMeshContainer = pFrame->pMeshContainer;

	while (pMeshContainer)
	{
		// メッシュコンテナの描画
		RenderMeshContainer(pMeshContainer, pFrame);
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

void CRenderModel::RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase)
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

		for (DWORD i = 0; i < pMeshContainer->dwBone; ++i)
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

			CDirectxMgr::Getintance().GetDxDevice()->SetRenderState(D3DRS_VERTEXBLEND, dwBlendMatrix);
			
			for (DWORD k = 0; k < pMeshContainer->dwWeight; k++)
			{
				DWORD id = pBoneCombi[i].BoneId[k];

				if (id != UINT_MAX)
				{
					CDirectxMgr::Getintance().GetDxDevice()->SetTransform(D3DTS_WORLDMATRIX(k), &(pMeshContainer->pBoneOffsetMatrix[id] * (*pMeshContainer->ppBoneMatrix[id]) ));
				}
			}
			
			CDirectxMgr::Getintance().GetDxDevice()->SetMaterial(&pMeshContainer->pMaterials[pBoneCombi[i].AttribId].MatD3D);
			CDirectxMgr::Getintance().GetDxDevice()->SetTexture(0, pMeshContainer->ppTextures[pBoneCombi[i].AttribId]);
			dwPrevBoneID = pBoneCombi[i].AttribId;
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}
		// スキン情報のあるモデルの描画完了
		return;
	}

	// スキンなしモデル
	CDirectxMgr::Getintance().GetDxDevice()->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);
	for (DWORD iAttrib = 0; iAttrib < pMeshContainer->NumMaterials; ++iAttrib) {
		DWORD dwAttrib = pMeshContainer->pAttributeTable[iAttrib].AttribId;
		CDirectxMgr::Getintance().GetDxDevice()->SetMaterial(&pMeshContainer->pMaterials[dwAttrib].MatD3D);
		CDirectxMgr::Getintance().GetDxDevice()->SetTexture(0, pMeshContainer->ppTextures[dwAttrib]);
		pMeshContainer->MeshData.pMesh->DrawSubset(dwAttrib);
	}

}

HRESULT CRenderModel::AllocBoneMatrix(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	if (pMeshContainer->pSkinInfo == NULL)
		return S_OK;	// スキン情報が無ければ何もしない
	DWORD dwBoneNum = pMeshContainer->pSkinInfo->GetNumBones();
	pMeshContainer->ppBoneMatrix = new LPD3DXMATRIX[dwBoneNum];
	for (DWORD i = 0; i < dwBoneNum; ++i) {
		MYFRAME* pFrame = (MYFRAME*)D3DXFrameFind(m_FrameRoot,
			pMeshContainer->pSkinInfo->GetBoneName(i));
		if (pFrame == NULL)
			return E_FAIL;
		pMeshContainer->ppBoneMatrix[i] =
			&pFrame->CombinedTransformationMatrix;
	}
	return S_OK;
}

HRESULT CRenderModel::AllocAllBoneMatrix(LPD3DXFRAME pFrameBase)
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

void CRenderModel::SwitchAnimSet(UINT uAnimSet)
{
	if (uAnimSet >= m_NumAnimSet || m_AnimCtrl == NULL)
		return;
	m_AnimCtrl->SetTrackAnimationSet(0, m_AnimSet[uAnimSet]);
}

void CRenderModel::SetTime(double dTime)
{
	if (m_AnimCtrl == NULL)
		return;

	for (DWORD i = 0; i < m_AnimCtrl->GetMaxNumTracks(); ++i)
	{
		m_AnimCtrl->SetTrackPosition(i, 0);
	}
	m_AnimCtrl->ResetTime();
	m_AnimCtrl->AdvanceTime(dTime, NULL);
}

D3DXMATRIX* CRenderModel::SerchBorn(LPSTR BornName)
{
	return GetBorn(m_FrameRoot, BornName);
}

D3DXMATRIX* CRenderModel::GetBorn(LPD3DXFRAME pFrameBase, LPSTR BornName)
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
//		対象物（坂とか）の角度の取得と計算？
//
/////////////////////////////////////////////////////////////////////////
bool CRenderModel::Intersect(D3DXVECTOR3& L0,
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
	return IntersectFrame(m_FrameRoot, L0, W, bRay, pCross, pNormal);
}

/////////////////////////////////////////////////////////////////////////
//
//		上の計算結果から結果の返信？
//
/////////////////////////////////////////////////////////////////////////
bool CRenderModel::IntersectFrame(LPD3DXFRAME pFrameBase,
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
bool CRenderModel::IntersectMeshContainer(
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