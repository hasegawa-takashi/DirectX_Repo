#include "Field.h"
#include"RenderMgr.h"

#define PATH_MESHLAND	_T("../data/model/Field.x")

CField::CField()
{
	m_bLoad = false;
}


CField::~CField()
{
}

// ������
void CField::Init()
{

	m_ModelMesh = new CMeshRender;
	if (!m_bLoad) {
		m_bLoad = m_ModelMesh->Initialize(PATH_MESHLAND);
	}
	/*if (m_bLoad) {
		SetMesh(&m_mesh);
	}*/
	ObjNumb = CObjManager::Instance()->RenameObj(ID_FIELD);

	D3DXMatrixIdentity(&m_mtxWorld);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	CObjManager::Instance()->LateRenderPush(this);


}


// ������
void CField::Update()
{
	m_ModelMesh->Update(m_mtxWorld);
}


// ���
void CField::Draw()
{

	CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// ���ʔ��˂𖳌�
	if (m_bLoad)
		m_ModelMesh->Render();

	CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, FALSE);	// ���ʔ��˂𖳌�
}

// ���
void CField::Release()
{
	if (m_bLoad) {
		m_bLoad = false;
		m_ModelMesh->Finalize();
		delete m_ModelMesh;
	}
}