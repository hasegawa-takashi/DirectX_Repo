#include "Player.h"



CPlayer::CPlayer()
{
	
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Init()
{
	m_Position = D3DXVECTOR3(0,0,0);
	m_MoveSpd = 0.1f;
	m_RenderModel = new CRenderModel("../data/model/box.x");
	m_Collision = new ColBox(this);

	D3DXMatrixIdentity(&m_WorldMtx);

	m_WorldMtx._41 = m_Position.x;
	m_WorldMtx._42 = m_Position.y;
	m_WorldMtx._43 = m_Position.z;

	CCamera::Getintance().SetTargetObj(this);

}

void CPlayer::Update()
{
	Move();

	RotateDir();

	ChangeDir();

	MoveResult();

}

void CPlayer::ChangeDir()
{
	// プレイヤーの向きの設定
	D3DXMATRIX rot;
	D3DXVECTOR3 View;

	View = (m_Position - CCamera::Getintance().GetPosition());

	D3DXMatrixRotationY(&rot, D3DXToRadian(m_DirectionAngle));
	D3DXVec3TransformCoord(&View, &View, &rot);

	D3DXVECTOR3 ZVec = View;
	D3DXVECTOR3 YVec = m_WorldMtx.m[1];
	D3DXVECTOR3 XVec;

	D3DXVec3Cross(&XVec, &ZVec, &YVec);
	D3DXVec3Normalize(&XVec, &XVec);
	D3DXVec3Cross(&ZVec, &YVec, &XVec);
	D3DXVec3Normalize(&ZVec, &ZVec);

	memcpy(m_WorldMtx.m[0], &XVec, sizeof(D3DXVECTOR3));
	memcpy(m_WorldMtx.m[2], &-ZVec, sizeof(D3DXVECTOR3));

}

void CPlayer::Move()
{
	m_Movement = D3DXVECTOR3(0,0,0);
	m_Inputstate = 0x00000000;

	if (CInput::GetKeyPress(DIK_A))
	{
		m_Movement.x -= m_MoveSpd;
		CCamera::Getintance().TargetMove();
		m_Inputstate += Left;
	}

	if (CInput::GetKeyPress(DIK_D))
	{
		m_Movement.x += m_MoveSpd;
		CCamera::Getintance().TargetMove();
		m_Inputstate += Right;
	}

	if (CInput::GetKeyPress(DIK_W))
	{
		m_Movement.z += m_MoveSpd;
		CCamera::Getintance().TargetMove();
		m_Inputstate += Forwad;
	}

	if (CInput::GetKeyPress(DIK_S))
	{
		m_Movement.z -= m_MoveSpd;
		CCamera::Getintance().TargetMove();
		m_Inputstate += Back;
	}

	if (m_Inputstate == FL ||
		m_Inputstate == FR ||
		m_Inputstate == BL ||
		m_Inputstate == BR)
	{
		m_Movement.z /= sqrtf(2);
	}

}

void CPlayer::RotateDir()
{
	switch (m_Inputstate)
	{
	case Forwad:
		m_DirectionAngle = 0.0f;
		break;

	case Left:
		m_DirectionAngle = -90.0f;
		break;

	case Right:
		m_DirectionAngle = 90.0f;
		break;

	case Back:
		m_DirectionAngle = 180.0f;
		break;

	case FL:
		m_DirectionAngle = -45.0f;
		break;

	case FR:
		m_DirectionAngle = 45.0f;
		break;

	case BL:
		m_DirectionAngle = -135.0f;
		break;

	case BR:
		m_DirectionAngle = 135.0f;
		break;

	default:
		break;
	}

}

void CPlayer::MoveResult()
{
	//D3DXVECTOR3 View;
	//View = (m_Position - CCamera::Getintance().GetPosition());

	// 移動の最終的な反映
	m_Position.x = m_WorldMtx._41 += m_Movement.x;
	m_Position.y = m_WorldMtx._42 += m_Movement.y;
	m_Position.z = m_WorldMtx._43 -= (m_WorldMtx.m[2][2] * m_Movement.z);

	// 座標に反映
	m_RenderModel->AnimationUpdate(m_WorldMtx);

	CDebug::Getintance().Conversion("プレイヤー座標(VECTOR)" ,m_Position);

}

void CPlayer::Draw()
{
	m_RenderModel->RenderModel();
}

void CPlayer::Release()
{
	delete m_RenderModel;
}