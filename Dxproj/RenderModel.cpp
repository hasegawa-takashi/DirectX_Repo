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
	// �o�ߎ��Ԍv���p�����ݒ�
	m_Prev = ::timeGetTime();
	
	return SUCCEEDED(hr);
}

void CRenderModel::Release()
{
	// �A�j���[�V�����j��
	if (m_AnimSet) {
		for (DWORD u = 0; u < m_NumAnimSet; ++u) {
			Complete_type_safe_delete(m_AnimSet[u]);
		}
		Complete_type_safe_delete(m_AnimSet);
	}
	Complete_type_safe_delete(m_AnimCtrl);

	// ���b�V���j��
	if (m_FrameRoot) {
		D3DXFrameDestroy(m_FrameRoot, &m_Hierarchy);
		m_FrameRoot = NULL;
	}
}

void CRenderModel::AnimationUpdate(D3DXMATRIX& world)
{
	// �A�j���[�V�����̍X�V
	if (m_AnimCtrl)
	{
		DWORD dwNow = ::timeGetTime();
		double d = (dwNow - m_Prev) / 1000.0;
		m_Prev = dwNow;
		m_AnimCtrl->AdvanceTime(d, NULL);
	}
	// �}�g���b�N�X�̍X�V
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
		// �t���[���`��
		DrawFrame(m_FrameRoot);
	}
}

void CRenderModel::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;

	// �e�̃}�g���b�N�X���|�����킹��
	if (pParentMatrix) {
		pFrame->CombinedTransformationMatrix =
			pFrame->TransformationMatrix * *pParentMatrix;
	}
	else {
		pFrame->CombinedTransformationMatrix =
			pFrame->TransformationMatrix;
	}

	// �Z��t���[��������΃}�g���b�N�X���X�V
	if (pFrame->pFrameSibling) {
		UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
	}

	// �q�t���[��������΃}�g���b�N�X���X�V
	if (pFrame->pFrameFirstChild) {
		// �������e�ƂȂ�̂ŁA�����̃}�g���b�N�X��n��
		UpdateFrameMatrices(pFrame->pFrameFirstChild,
			&pFrame->CombinedTransformationMatrix);
	}
}

void CRenderModel::DrawFrame(LPD3DXFRAME pFrame)
{
	LPD3DXMESHCONTAINER pMeshContainer = pFrame->pMeshContainer;

	while (pMeshContainer)
	{
		// ���b�V���R���e�i�̕`��
		RenderMeshContainer(pMeshContainer, pFrame);
		// ���̃��b�V���R���e�i
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}

	// �Z��t���[��������ΌZ��t���[���̕`��
	if (pFrame->pFrameSibling)
		DrawFrame(pFrame->pFrameSibling);
	// �t���[��������Ύq�t���[����`��
	if (pFrame->pFrameFirstChild)
		DrawFrame(pFrame->pFrameFirstChild);

}

void CRenderModel::RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase)
{
	// ���ꍞ��
	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;

	if (pMeshContainer->pSkinInfo)
	{
		// �X�L�����b�V�����f��

		// �{�[�����
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
		// �X�L�����̂��郂�f���̕`�抮��
		return;
	}

	// �X�L���Ȃ����f��
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
		return S_OK;	// �X�L����񂪖�����Ή������Ȃ�
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