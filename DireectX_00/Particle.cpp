#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include "Particle.h"

#define PATH_TEXTUREFNAME	TEXT("../data/texture/ParticleCloudWhite.png")

#define FVF_PVERTEX			(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#define frand()				(rand()/(float)RAND_MAX)

// �R���X�g���N�^
CParticle::CParticle()
{

}

// �f�X�g���N�^
CParticle::~CParticle(void){

}

// �X�V
void CParticle::Update(void)
{

}

void CParticle::Release(void)
{

}


void CParticle::Draw(void)
{
	// �`�悵�Ȃ�
}

void CParticle::LateDraw(void)
{
	
}
					   