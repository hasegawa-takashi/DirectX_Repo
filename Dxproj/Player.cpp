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
	m_PlayerModel = new CRenderModel("../data/model/Cube.x");
	//m_PlayerModel = new CRenderNonMesh("../data/model/Field.x");

	D3DXMatrixIdentity(&m_WorldMtx);

	m_WorldMtx._41 = m_Position.x;
	m_WorldMtx._42 = m_Position.y;
	m_WorldMtx._43 = m_Position.z;

	CCamera::Getintance().SetTargetObj(this);

}

void CPlayer::Update()
{
	Move();

	MoveResult();

}

void CPlayer::Move()
{
	m_Movement = D3DXVECTOR3(0,0,0);
	int _inputstate = 0x00000000;

	if (CInput::GetKeyPress(DIK_A))
	{
		m_Movement.x -= m_MoveSpd;
		CCamera::Getintance().TargetMove();
		_inputstate += Left;
	}

	if (CInput::GetKeyPress(DIK_D))
	{
		m_Movement.x += m_MoveSpd;
		CCamera::Getintance().TargetMove();
		_inputstate += Right;
	}

	if (CInput::GetKeyPress(DIK_W))
	{
		m_Movement.z += m_MoveSpd;
		CCamera::Getintance().TargetMove();
		_inputstate += Forwad;
	}

	if (CInput::GetKeyPress(DIK_S))
	{
		m_Movement.z -= m_MoveSpd;
		CCamera::Getintance().TargetMove();
		_inputstate += Back;
	}

	if (_inputstate == FL ||
		_inputstate == FR ||
		_inputstate == BL ||
		_inputstate == BR)
	{
		m_Movement.x /= sqrtf(2);
		m_Movement.z /= sqrtf(2);
	}

}

void CPlayer::MoveResult()
{
	// �ړ��̍ŏI�I�Ȕ��f
	m_Position.x += m_Movement.x;
	m_Position.z += m_Movement.z;


	// ���W�ɔ��f

	m_WorldMtx._41 = m_Position.x;
	m_WorldMtx._42 = m_Position.y;
	m_WorldMtx._43 = m_Position.z;

	m_PlayerModel->AnimationUpdate(m_WorldMtx);


}

void CPlayer::Draw()
{
	m_PlayerModel->RenderModel();

	CDebug::Getintance().Conversion("���W" ,m_Position);
}

void CPlayer::Release()
{
	delete m_PlayerModel;
}