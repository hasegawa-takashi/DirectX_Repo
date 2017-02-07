#pragma once

#include "MyHierarchy.h"
#include"Window.h"
#include"RenderMgr.h"

class CMeshRender
{
private:
	LPD3DXFRAME					m_pFrameRoot;	// ���[�g �t���[�� �I�u�W�F�N�g
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;	// �A�j���[�V���� �R���g���[�� �I�u�W�F�N�g
	UINT						m_uNumAnimSet;	// �A�j���[�V���� �Z�b�g��
	LPD3DXANIMATIONSET*			m_ppAnimSet;	// �A�j���[�V���� �Z�b�g
	CMyHierarchy				m_Hierarchy;	// �K�w�������m��/����N���X
	DWORD						m_dwPrev;		// ���O�̎���

public:
	CMeshRender();
	~CMeshRender();

	bool Initialize(LPCTSTR pszFName);		// ���b�V��������
	void Finalize();						// ���b�V�����
	void Update(D3DXMATRIX& world);			// ���b�V���X�V
	void Render();							// ���b�V���`��
	void SwitchAnimSet(UINT uAnimSet);		// �A�j���[�V�����ؑ�
	void SetTime(double dTime);				// �A�j���[�V�����J�n���Ԑݒ�

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

