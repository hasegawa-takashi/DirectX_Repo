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
CParticle::~CParticle(void){

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
					   