#include "Enemy.h"



CEnemy::CEnemy(float spd)
{
	m_NonDeleteObj = false;

	m_Position = D3DXVECTOR3((float)(rand() % 8 - 4), (float)(rand() % 8 - 4), 100.0f );
	m_MoveSpd = spd;
	m_RenderModel = new CRenderModel("../data/model/Enemybox.x");
	m_Collision = new ColBox(this);
	m_Velocity = D3DXVECTOR3(0,0, m_MoveSpd);
	D3DXMatrixIdentity(&m_WorldMtx);

	m_WorldMtx._41 = m_Position.x;
	m_WorldMtx._42 = m_Position.y;
	m_WorldMtx._43 = m_Position.z;

	//ÉRÉäÉWÉáÉìÇÃê›íË
	m_Collision->WorldMtx = m_WorldMtx;
	m_Collision->m_Pos = m_Position;
	m_Collision->Radius = 0.5f;
	m_Collision->ModelMesh = m_RenderModel;
	CCollisionMgr::Getintance().SetCollision(m_Collision);

	m_CrossSound.EmitterComp = m_CrossSound.Comp.AddComponent<CEmitterComponent>();
	m_CrossSound.Playercomp = m_CrossSound.Comp.AddComponent<CSoundPlayerComponent>();
	m_CrossSound.EffectComp = m_CrossSound.Comp.AddComponent<CSoundEffectComponent>();
	
	m_CrossSound.Sourcevoice = *(m_CrossSound.Playercomp->Init("Se", "cross"));

	m_CrossSound.EmitterComp->Init(&m_CrossSound.Sourcevoice, &m_WorldMtx);
	m_CrossSound.EmitterComp->MoveVelocity( &m_Velocity );

	m_CrossSound.EffectComp->Init(m_CrossSound.Sourcevoice);
	m_CrossSound.EffectComp->SetSpaceEffect();
}

void CEnemy::HitEnemy()
{
	m_HitObj = CCollisionMgr::Getintance().CheckHitObj(m_Collision, COL_SPHERE);

	if (!m_HitObj.empty())
	{
		for each (auto var in m_HitObj)
		{
			if (var->GetObjName() == ID_TUNNEL)
			{
				m_CrossSound.EffectComp->SetTunnelEffect();
				m_CrossSound.EffectComp->offsetSpaceEffect();
			}
		}
	}
	else
	{
		m_CrossSound.EffectComp->offsetTunnelEffect();
		m_CrossSound.EffectComp->SetSpaceEffect();
	}
}


CEnemy::~CEnemy()
{
	m_CrossSound.Comp.ClearComponent();

	delete m_Collision;
	delete m_RenderModel;
}

void CEnemy::Init()
{

}

void CEnemy::Update()
{
	Move();
	MoveResult();
	AutoDestroy();

	m_CrossSound.Comp.ComponentUpdate();
	m_FallVoice.Comp.ComponentUpdate();

	if (m_Position.z < 0 && m_Position.z > -10)
	{
		CAudioDatabase::Instance()->ChangeCueVolume("Bgm",0.5f);
		m_CrossSound.Playercomp->Play();
	}

}

void CEnemy::Draw()
{
	m_RenderModel->RenderModel();
}

void CEnemy::Release()
{
	
}

void CEnemy::Move()
{
	m_Movement = D3DXVECTOR3(0,0,0);
	m_Movement.z -= m_MoveSpd;
}


void CEnemy::MoveResult()
{
	m_Position.z = m_WorldMtx._43 += m_Movement.z;

	m_RenderModel->AnimationUpdate(m_WorldMtx);
	
	m_Collision->WorldMtx = m_WorldMtx;
	m_Collision->m_Pos = m_Position;

}

/// <summary>
/// é©ìÆÇ≈âÛÇÍÇÈÇÊÇ§Ç…ê›íË
/// </summary>
void CEnemy::AutoDestroy()
{
	if (m_WorldMtx._43 <= -15)
	{
		if (m_CrossSound.Playercomp->EndSoundflag() == true)
		{
			CAudioDatabase::Instance()->ChangeCueVolume("Bgm", 1.0f);
			CCollisionMgr::Getintance().DeleteCollision(m_Collision);
			CObjMgr::Getintance().PopObj(m_ObjID, m_ObjNumb);
		}
	}
}