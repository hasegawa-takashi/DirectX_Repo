#include "Goal.h"


CGoal::CGoal()
{
}


CGoal::~CGoal()
{
}

void CGoal::Init()
{

	D3DXMatrixIdentity(&m_mtxWorld);

	m_Collision.m_Pos = D3DXVECTOR3(-58.0f, 1.0f, 142);

	m_Collision.m_fLength[0] = 5;
	m_Collision.m_fLength[1] = 5;
	m_Collision.m_fLength[2] = 5;

	m_Collision.WorldMtx = m_mtxWorld;

}

void CGoal::Update()
{

}

void CGoal::LateUpdate()
{

}

void CGoal::Draw()
{

}

void CGoal::LateDraw()
{

}

void CGoal::Release()
{

}

void CGoal::Pause()
{

}
