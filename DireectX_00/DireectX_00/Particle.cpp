#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include "Particle.h"

#define PATH_TEXTUREFNAME	TEXT("../data/texture/ParticleCloudWhite.png")

#define FVF_PVERTEX			(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#define frand()				(rand()/(float)RAND_MAX)

// コンストラクタ
CParticle::CParticle()
{

}

// デストラクタ
CParticle::~CParticle(void)
{
	Release();
}

// 更新
void CParticle::Update(void)
{

}

void CParticle::Release(void)
{

}


void CParticle::Draw(void)
{
	// 描画しない
}

void CParticle::LateDraw(void)
{
	
}

void CParticle::SetPos(D3DXVECTOR3 pos)
{
	m_mtxWorld._41 = pos.x;
	m_mtxWorld._42 = pos.y;
	m_mtxWorld._43 = pos.z;
}

D3DXVECTOR3 CParticle::GetPos()
{
	return D3DXVECTOR3(m_mtxWorld._41,m_mtxWorld._42, m_mtxWorld._43);
}					   