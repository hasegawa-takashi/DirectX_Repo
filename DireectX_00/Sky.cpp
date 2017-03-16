// �X�J�C�h�[�� �N���X����

#include "Sky.h"
#include "Camera.h"

// �萔
#define PATH_MESHSKY	_T("../data/model/sky.x")

// �R���X�g���N�^
CSky::CSky()
{

}

// �f�X�g���N�^
CSky::~CSky(void)
{
}

// ������
void CSky::Init()
{
	m_ModelMesh = new CMeshRender;
	m_ModelMesh->Initialize(PATH_MESHSKY);
	
	// �J�����I�u�W�F�N�g�̎擾
	CameraObj = GetObjMgr()->SerchObj(ID_CAMERA);

}

// �X�V
void CSky::Update()
{
}

// �X�V�㏈��
void CSky::LateUpdate()
{
	D3DXVECTOR3 pos;

	for (auto& p : CameraObj)
	{
		pos = p->GetPos();
	}

	D3DXMATRIX world;
	D3DXMatrixTranslation(&world, pos.x, pos.y, pos.z);

	m_mtxWorld = world;

	m_ModelMesh->Update(m_mtxWorld);

}

// �`��
void CSky::Draw()
{
	// �������Ȃ�
	LPDIRECT3DDEVICE9 pD = GetDxMgr()->GetDxDevice();
	pD->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_ModelMesh->Render();
	pD->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pD->SetRenderState(D3DRS_LIGHTING, TRUE);

}

// �������`��
void CSky::LateDraw()
{
	

}

// ���
void CSky::Release()
{
	//m_ModelMesh->Finalize();
	delete m_ModelMesh;
}