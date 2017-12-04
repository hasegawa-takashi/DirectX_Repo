#include "Player.h"

CPlayer::CPlayer()
{
	m_Alive = true;
	m_Invisible = false;
	m_Position = D3DXVECTOR3(0, 0, 0);
	m_MoveSpd = 0.1f;
	m_RenderModel = new CRenderModel("../data/model/Player.x");
	m_Collision = new ColBox(this);

	D3DXMatrixIdentity(&m_WorldMtx);

	m_WorldMtx._41 = m_Position.x;
	m_WorldMtx._42 = m_Position.y;
	m_WorldMtx._43 = m_Position.z;

	CCamera::Getintance().SetTargetObj(this);

	//コリジョンの設定
	m_Collision->WorldMtx = m_WorldMtx;
	m_Collision->m_Pos = m_Position;
	m_Collision->Radius = 0.5f;
	m_Collision->ModelMesh = m_RenderModel;
	CCollisionMgr::Getintance().SetCollision(m_Collision);

	m_BombVoice.Playercomp = m_BombVoice.Comp.AddComponent<CSoundPlayerComponent>();
	m_BombVoice.Sourcevoice = *(m_BombVoice.Playercomp->Init("Se", "bomb"));
	m_BombVoice.EffectComp = m_BombVoice.Comp.AddComponent<CSoundEffectComponent>();
	m_BombVoice.EffectComp->Init(m_BombVoice.Sourcevoice);
	m_BombVoice.EffectComp->SetSpaceEffect();

	// サウンドの設定
	m_FallVoice.ListenerComp = m_FallVoice.Comp.AddComponent<CListenerComponent>();
	m_FallVoice.Playercomp = m_FallVoice.Comp.AddComponent<CSoundPlayerComponent>();
	m_FallVoice.EffectComp = m_FallVoice.Comp.AddComponent<CSoundEffectComponent>();
	m_FallVoice.Sourcevoice = *(m_FallVoice.Playercomp->Init("Se", "UFO"));
	m_FallVoice.ListenerComp->Init(&m_WorldMtx);
	m_FallVoice.EffectComp->Init(m_FallVoice.Sourcevoice);
	m_FallVoice.EffectComp->SetSpaceEffect();

	//　再生
	m_FallVoice.Playercomp->Play();
}


CPlayer::~CPlayer()
{
	m_BombVoice.Comp.ClearComponent();
	m_FallVoice.Comp.ClearComponent();
	
	delete m_Collision;
	delete m_RenderModel;

	m_HitObj.clear();
}

void CPlayer::Init()
{
	m_Alive = true;
	m_Position = D3DXVECTOR3(0, 0, 0);
	m_MoveSpd = 0.2f;

	D3DXMatrixIdentity(&m_WorldMtx);

	m_WorldMtx._41 = m_Position.x;
	m_WorldMtx._42 = m_Position.y;
	m_WorldMtx._43 = m_Position.z;

	CCamera::Getintance().SetTargetObj(this);

	//コリジョンの設定
	m_Collision->WorldMtx = m_WorldMtx;
	m_Collision->m_Pos = m_Position;
	m_Collision->Radius = 3.0f;
	m_Collision->ModelMesh = m_RenderModel;
	CCollisionMgr::Getintance().SetCollision(m_Collision);

	m_HitObj.clear();

}

void CPlayer::Update()
{
	Move();

	RotateDir();
	
	MoveResult();

	if (m_Alive)
	{
		HitPlayer();
	}
	
	// サウンドコンポーネントのアップデート
	m_FallVoice.Comp.ComponentUpdate();
	m_BombVoice.Comp.ComponentUpdate();
}

void CPlayer::Move()
{
	m_Movement = D3DXVECTOR3(0,0,0);
	m_Inputstate = 0x00000000;

	if (CInput::GetKeyPress(DIK_A) && m_Position.x > -4)
	{
		m_Movement.x -= m_MoveSpd;
		CCamera::Getintance().TargetMove();
		m_Inputstate += Left;
	}

	if (CInput::GetKeyPress(DIK_D) && m_Position.x < 4)
	{
		m_Movement.x += m_MoveSpd;
		CCamera::Getintance().TargetMove();
		m_Inputstate += Right;
	}

	if (CInput::GetKeyPress(DIK_W) && m_Position.y < 4)
	{
		m_Movement.y += m_MoveSpd;
		CCamera::Getintance().TargetMove();
		m_Inputstate += Forwad;
	}

	if (CInput::GetKeyPress(DIK_S) && m_Position.y > -4)
	{
		m_Movement.y -= m_MoveSpd;
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
	/*switch (m_Inputstate)
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
	}*/
	m_DirectionAngle=0.01f;
}

void CPlayer::MoveResult()
{
	D3DXMATRIX roty, scale, transform;

	D3DXMatrixRotationY(&roty, m_DirectionAngle);

	D3DXMatrixMultiply(&m_WorldMtx,&roty,&m_WorldMtx);

	// 移動の最終的な反映
	m_Position.x = m_WorldMtx._41 += m_Movement.x;
	m_Position.y = m_WorldMtx._42 += m_Movement.y;
	m_Position.z = m_WorldMtx._43 += (/*m_WorldMtx.m[2][2] */ m_Movement.z);

	// 座標に反映
	m_RenderModel->AnimationUpdate(m_WorldMtx);

	m_Collision->WorldMtx = m_WorldMtx;
	m_Collision->m_Pos = m_Position;
}

void CPlayer::HitPlayer()
{
	m_HitObj = CCollisionMgr::Getintance().CheckHitObj(m_Collision, COL_SPHERE);

	if (!m_HitObj.empty())
	{
		for each (auto var in m_HitObj)
		{
			if (var->GetObjName() == ID_ENEMY)
			{
				if (m_Invisible == false)
				{
					// 死亡判定
					m_Alive = false;
					CCamera::Getintance().SetTargetObj(nullptr);

					m_FallVoice.Playercomp->FadeStop(1);
					m_BombVoice.Playercomp->Play();

					CCollisionMgr::Getintance().DeleteCollision(m_Collision);

					CObjMgr::Getintance().PopObj(var->GetObjName(), var->GetidentNumb());

					CSceneMgr::Getintance().PushScene<CTitleScene>();
					CObjMgr::Getintance().PushObj(new CBlackoutFade, ID_FADE);
				}
			}

			if (var->GetObjName() == ID_TUNNEL)
			{
				m_BombVoice.EffectComp->SetTunnelEffect();
				m_FallVoice.EffectComp->SetTunnelEffect();
				m_BombVoice.EffectComp->offsetSpaceEffect();
				m_FallVoice.EffectComp->offsetSpaceEffect();
			}
		}
	}
	else
	{
		m_BombVoice.EffectComp->SetSpaceEffect();
		m_FallVoice.EffectComp->SetSpaceEffect();
		m_BombVoice.EffectComp->offsetTunnelEffect();
		m_FallVoice.EffectComp->offsetTunnelEffect();
	}
}

void CPlayer::Draw()
{
	if (m_Alive)
	{
		m_RenderModel->RenderModel();
	}
}

void CPlayer::Release()
{
	CCollisionMgr::Getintance().DeleteCollision(m_Collision);
}