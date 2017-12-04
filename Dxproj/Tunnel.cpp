#include "Tunnel.h"



CTunnel::CTunnel()
{
	m_Position = D3DXVECTOR3(0,0, 500);
	m_MoveSpd = 0.8f;
	m_RenderModel = new CRenderModel("../data/model/tunnel.x");
	m_Collision = new ColBox(this);
	m_Velocity = D3DXVECTOR3(0, 0, m_MoveSpd);
	D3DXMatrixIdentity(&m_WorldMtx);
	m_WorldMtx._41 = m_Position.x;
	m_WorldMtx._42 = m_Position.y;
	m_WorldMtx._43 = m_Position.z;

	m_Collision->WorldMtx = m_WorldMtx;
	m_Collision->m_Pos = m_Position;
	m_Collision->Radius = 150.0f;
	m_Collision->ModelMesh = m_RenderModel;
	CCollisionMgr::Getintance().SetCollision(m_Collision);

}


CTunnel::~CTunnel()
{
	delete m_RenderModel;	
	delete m_Collision;
}

void CTunnel::Draw()
{
	m_RenderModel->RenderModel();
}

void CTunnel::Update()
{
	m_Movement = D3DXVECTOR3(0, 0, 0);
	m_Movement.z -= m_MoveSpd;

	MoveResult();
	AutoDestroy();	
}

void CTunnel::MoveResult()
{
	m_Position.z = m_WorldMtx._43 += m_Movement.z;

	m_RenderModel->AnimationUpdate(m_WorldMtx);

	m_Collision->WorldMtx = m_WorldMtx;
	m_Collision->m_Pos = m_Position;

}

/// <summary>
/// ©“®‚Å‰ó‚ê‚é‚æ‚¤‚Éİ’è
/// </summary>
void CTunnel::AutoDestroy()
{
	if (m_WorldMtx._43 <= -15)
	{
		CCollisionMgr::Getintance().DeleteCollision(m_Collision);
		CObjMgr::Getintance().PopObj(m_ObjID, m_ObjNumb);
	}
}