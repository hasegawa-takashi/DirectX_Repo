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

// ‰Šú‰»
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


// ‰Šú‰»
void CField::Update()
{
	m_ModelMesh->Update(m_mtxWorld);
}


// ‰ð•ú
void CField::Draw()
{

	CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// ‹¾–Ê”½ŽË‚ð–³Œø
	if (m_bLoad)
		m_ModelMesh->Render();

	CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, FALSE);	// ‹¾–Ê”½ŽË‚ð–³Œø
}

// ‰ð•ú
void CField::Release()
{
	if (m_bLoad) {
		m_bLoad = false;
		m_ModelMesh->Finalize();
		delete m_ModelMesh;
	}
}