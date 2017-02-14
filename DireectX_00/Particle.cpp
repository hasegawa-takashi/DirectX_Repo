//#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_NON_CONFORMING_SWPRINTFS
//#include "Particle.h"
//
//#define PATH_TEXTUREFNAME	TEXT("../data/texture/ParticleCloudWhite.png")
//
//#define FVF_PVERTEX			(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
//
//#define frand()				(rand()/(float)RAND_MAX)
//
//// �R���X�g���N�^
//CParticle::CParticle()
//{
//	m_pTexture = NULL;
//	m_szTexFName[0] = _T('\0');
//
//	m_synthetic = m_pp.synthetic;
//	m_fTime = 0.0f;
//	m_fRate = 0.0f;
//	m_uParticles = m_pp.uMaxParticles;
//
//	m_pGrain = NULL;
//	m_pUse = NULL;
//	m_uUse = 0;
//	m_pUnused = NULL;
//
//	m_pVertex = NULL;
//	m_pIndex = NULL;
//}
//
//// �f�X�g���N�^
//CParticle::~CParticle(void)
//{
//	Release();
//}
//
//// �e�N�X�`���X�V
//void CParticle::UpdateTexture(void)
//{
//	D3DXIMAGE_INFO info;
//	ZeroMemory(&info, sizeof(info));
//	if (m_pp.szTexFName[0]) {
//		if (m_pTexture) {
//			if (lstrcmpi(m_pp.szTexFName, m_szTexFName) == 0) {
//				return;
//			}
//			SAFE_RELEASE(m_pTexture);
//			m_szTexFName[0] = _T('\0');
//		}
//		if (FAILED(D3DXCreateTextureFromFileEx(CWindow::Instance()->GetDevice(),
//			m_pp.szTexFName, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0,
//			D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT,
//			D3DX_DEFAULT, 0, &info, NULL, &m_pTexture))) {
//			m_pTexture = NULL;
//			m_szTexFName[0] = _T('\0');
//		} else {
//			lstrcpy(m_szTexFName, m_pp.szTexFName);
//		}
//	} else {
//		SAFE_RELEASE(m_pTexture);
//		m_szTexFName[0] = _T('\0');
//	}
//}
//
//// �p�����[�^�X�V
//void CParticle::SetParam(TParticleParam& pp)
//{
//	m_pp = pp;
//	if (m_pp.fStartSpeed > m_pp.fStartSpeed2) {
//		float fSpeed = m_pp.fStartSpeed;
//		m_pp.fStartSpeed = m_pp.fStartSpeed2;
//		m_pp.fStartSpeed2 = fSpeed;
//	}
//	if (m_pp.fStartSize > m_pp.fStartSize2) {
//		float fSize = m_pp.fStartSize;
//		m_pp.fStartSize = m_pp.fStartSize2;
//		m_pp.fStartSize2 = fSize;
//	}
//	if (m_pp.fStartRotation > m_pp.fStartRotation2) {
//		float fRotation = m_pp.fStartRotation;
//		m_pp.fStartRotation = m_pp.fStartRotation2;
//		m_pp.fStartRotation2 = fRotation;
//	}
//	if (m_pp.fStartLifetime > m_pp.fStartLifetime2) {
//		float fLifetime = m_pp.fStartLifetime;
//		m_pp.fStartLifetime = m_pp.fStartLifetime2;
//		m_pp.fStartLifetime2 = fLifetime;
//	}
//	UINT uA = HIBYTE(HIWORD(m_pp.cStartColor));
//	UINT uR = LOBYTE(HIWORD(m_pp.cStartColor));
//	UINT uG = HIBYTE(LOWORD(m_pp.cStartColor));
//	UINT uB = LOBYTE(m_pp.cStartColor);
//	UINT uA2 = HIBYTE(HIWORD(m_pp.cStartColor2));
//	UINT uR2 = LOBYTE(HIWORD(m_pp.cStartColor2));
//	UINT uG2 = HIBYTE(LOWORD(m_pp.cStartColor2));
//	UINT uB2 = LOBYTE(m_pp.cStartColor2);
//	bool bChange = false;
//	if (uA > uA2) {UINT u = uA; uA = uA2; uA2 = u;bChange = true;}
//	if (uR > uR2) {UINT u = uR; uR = uR2; uR2 = u;bChange = true;}
//	if (uG > uG2) {UINT u = uG; uG = uG2; uG2 = u;bChange = true;}
//	if (uB > uB2) {UINT u = uB; uB = uB2; uB2 = u;bChange = true;}
//	if (bChange) {
//		m_pp.cStartColor = D3DCOLOR_ARGB(uA, uR, uG, uB);
//		m_pp.cStartColor2 = D3DCOLOR_ARGB(uA2, uR2, uG2, uB2);
//	}
//	m_fTime = 0.0f;
//	m_fRate = 0.0f;
//	m_uParticles = m_pp.uMaxParticles;
//	m_synthetic = m_pp.synthetic;
//
//	UpdateTexture();
//}
//
//void CParticle::Init()
//{
//	//m_pCamera = (CCamera*)Find(ID_CAMERA);
//
//	SAFE_DELETE_ARRAY(m_pIndex);
//	SAFE_DELETE_ARRAY(m_pVertex);
//	SAFE_DELETE_ARRAY(m_pGrain);
//	m_pUse = m_pUnused = NULL;
//
//	UpdateTexture();
//
//	m_pGrain = new TGrain[m_pp.uMaxParticles];
//	m_pGrain[0].m_pBack = NULL;
//	m_pGrain[0].m_pNext = &m_pGrain[1];
//	for (UINT i = 1; i < m_pp.uMaxParticles - 1; ++i) {
//		m_pGrain[i].m_pNext = &m_pGrain[i + 1];
//		m_pGrain[i].m_pBack = &m_pGrain[i - 1];
//	}
//	m_pGrain[m_pp.uMaxParticles - 1].m_pBack = &m_pGrain[m_pp.uMaxParticles - 2];
//	m_pGrain[m_pp.uMaxParticles - 1].m_pNext = NULL;
//	m_pUse = NULL;
//	m_uUse = 0;
//	m_pUnused = &m_pGrain[0];
//
//	m_pVertex = new TVertex[m_pp.uMaxParticles * 4];
//	m_pIndex = new WORD[m_pp.uMaxParticles * 6];
//}
//
//void CParticle::Release(void)
//{
//	SAFE_DELETE_ARRAY(m_pIndex);
//	SAFE_DELETE_ARRAY(m_pVertex);
//	SAFE_DELETE_ARRAY(m_pGrain);
//	m_pUse = m_pUnused = NULL;
//	SAFE_RELEASE(m_pTexture);
//}
//
//void CParticle::Delete(TGrain* p)
//{
//	if (p->m_pBack) {
//		p->m_pBack->m_pNext = p->m_pNext;
//	} else {
//		m_pUse = p->m_pNext;
//	}
//	if (p->m_pNext) {
//		p->m_pNext->m_pBack = p->m_pBack;
//	}
//
//	p->m_pBack = NULL;
//	p->m_pNext = m_pUnused;
//	if (m_pUnused) {
//		m_pUnused->m_pBack = p;
//	}
//	m_pUnused = p;
//
//	--m_uUse;
//}
//
//CParticle::TGrain* CParticle::New(void)
//{
//	if (m_pUnused) {
//		TGrain* p = m_pUnused;
//		m_pUnused = m_pUnused->m_pNext;
//		if (m_pUnused) {
//			m_pUnused->m_pBack = NULL;
//		}
//		p->m_pNext = m_pUse;
//		if (m_pUse) {
//			m_pUse->m_pBack = p;
//		}
//		m_pUse = p;
//
//		// �����l�ݒ�
//		p->m_pos = GetPos();		//�����̃|�W�V������ς��Ȃ��ƃ_���ł�
//		p->m_pos.y += m_pp.fStartSize2 * 0.5f;
//		if (m_pp.coord == eSpherical) {
//			p->m_accel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		} else {
//			p->m_accel = D3DXVECTOR3(0.0f, -m_pp.fGravity, 0.0f);
//		}
//		float a = 0.0f;									// �J�n�p
//		float b = D3DXToRadian(m_pp.fCornAngle / 2.0f);	// �I���p
//		float theta = acosf(cosf(a) - frand() * (cosf(a) - cosf(b)));
//		float r = sinf(theta);
//		float eta = frand() * 2.0f * D3DX_PI;
//		p->m_velocity.x = r * cosf(eta);
//		p->m_velocity.y = cosf(theta);
//		p->m_velocity.z = r * sinf(eta);
//		D3DXVec3Normalize(&p->m_velocity, &p->m_velocity);
//		p->m_pos += p->m_velocity * m_pp.fRadius;
//		p->m_startPos = p->m_pos;
//		switch (m_pp.coord) {
//		case eSpherical:
//			p->m_velocity.x = r;
//			p->m_velocity.y = D3DXToDegree(eta);
//			p->m_velocity.z = D3DXToDegree(theta);
//			break;
//		case eCylindrical:
//			p->m_velocity.x = r;
//			p->m_velocity.y = cosf(theta);
//			p->m_velocity.z = D3DXToDegree(theta);
//			break;
//		case eCartesian:
//		default:
//			break;
//		}
//		p->m_velocity *= m_pp.fStartSpeed + (m_pp.fStartSpeed2 - m_pp.fStartSpeed) * frand();
//		p->m_size = m_pp.fStartSize + (m_pp.fStartSize2 - m_pp.fStartSize) * frand();
//		p->m_startSize = p->m_size;
//		p->m_angle = m_pp.fStartRotation + (m_pp.fStartRotation2 - m_pp.fStartRotation) * frand();
//		UINT uA = HIBYTE(HIWORD(m_pp.cStartColor));
//		UINT uR = LOBYTE(HIWORD(m_pp.cStartColor));
//		UINT uG = HIBYTE(LOWORD(m_pp.cStartColor));
//		UINT uB = LOBYTE(m_pp.cStartColor);
//		UINT uA2 = HIBYTE(HIWORD(m_pp.cStartColor2));
//		UINT uR2 = LOBYTE(HIWORD(m_pp.cStartColor2));
//		UINT uG2 = HIBYTE(LOWORD(m_pp.cStartColor2));
//		UINT uB2 = LOBYTE(m_pp.cStartColor2);
//		uA += (uA2 - uA) * rand() / RAND_MAX;
//		uR += (uR2 - uR) * rand() / RAND_MAX;
//		uG += (uG2 - uG) * rand() / RAND_MAX;
//		uB += (uB2 - uB) * rand() / RAND_MAX;
//		p->m_color = D3DCOLOR_ARGB(uA, uR, uG, uB);
//		p->m_startColor = p->m_color;
//		p->m_lifetime = m_pp.fStartLifetime + (m_pp.fStartLifetime2 - m_pp.fStartLifetime) * frand();
//		p->m_startLifetime = p->m_lifetime;
//
//		++m_uUse;
//		return p;
//	}
//	return NULL;
//}
//
//// �X�V
//void CParticle::Update(void)
//{
//	// �o�ߎ��� (�����ԂɕύX���������ǂ�)
//	float fDeltaTime = 1.0f / 60.0f;
//
//	// ����
//	if (m_uParticles) {
//		m_fRate += m_pp.uRate * fDeltaTime;
//		while (m_fRate >= 1.0f) {
//			m_fRate -= 1.0f;
//			--m_uParticles;
//			New();
//		}
//	}
//
//	D3DXMATRIX mView;
//
//	CWindow::Instance()->GetDevice()->GetTransform(D3DTS_VIEW,&mView);
//
//	D3DXMATRIX mBB(mView._11, mView._21, mView._31, 0.0f,
//				   mView._12, mView._22, mView._32, 0.0f,
//				   mView._13, mView._23, mView._33, 0.0f,
//				   0.0f, 0.0f, 0.0f, 1.0f);
//	D3DXMATRIX mRZ, mtx;
//	TGrain* pNext = NULL;
//	TVertex* pV = m_pVertex;
//	WORD* pI = m_pIndex;
//	WORD wIndex = 0;
//	for (TGrain* p = m_pUse; p; p = pNext) {
//		pNext = p->m_pNext;
//		// �X�V
//		p->m_lifetime -= fDeltaTime;
//		if (p->m_lifetime <= 0.0f) {
//			Delete(p);
//			continue;
//		}
//		p->m_velocity += p->m_accel * fDeltaTime;
//		p->m_pos += p->m_velocity * fDeltaTime;
//		if (p->m_pos.y <= -p->m_size * 2.0f) {
//			Delete(p);
//			continue;
//		}
//		float delta;
//		if (m_pp.bColorOverLifetime || m_pp.bSizeOverLifetime) {
//			delta = p->m_lifetime / p->m_startLifetime;
//		}
//		if (m_pp.bColorOverLifetime) {
//			int nA = HIBYTE(HIWORD(m_pp.cOverLifetime[0]));
//			int nR = LOBYTE(HIWORD(m_pp.cOverLifetime[0]));
//			int nG = HIBYTE(LOWORD(m_pp.cOverLifetime[0]));
//			int nB = LOBYTE(m_pp.cOverLifetime[0]);
//			int nA2 = HIBYTE(HIWORD(m_pp.cOverLifetime[1]));
//			int nR2 = LOBYTE(HIWORD(m_pp.cOverLifetime[1]));
//			int nG2 = HIBYTE(LOWORD(m_pp.cOverLifetime[1]));
//			int nB2 = LOBYTE(m_pp.cOverLifetime[1]);
//			nA = (int)(nA2 + (nA - nA2) * delta);
//			nR = (int)(nR2 + (nR - nR2) * delta);
//			nG = (int)(nG2 + (nG - nG2) * delta);
//			nB = (int)(nB2 + (nB - nB2) * delta);
//			p->m_color = D3DCOLOR_ARGB(nA, nR, nG, nB);
//		}
//		if (m_pp.bSizeOverLifetime) {
//			p->m_size = m_pp.fOverLifetime[1] + (m_pp.fOverLifetime[0] - m_pp.fOverLifetime[1]) * delta;
//		}
//		// ���_�\�z
//		D3DXMatrixRotationZ(&mRZ, D3DXToRadian(p->m_angle));
//		switch (m_pp.coord) {
//		case eCartesian:
//		default:
//			mBB._41 = p->m_pos.x;
//			mBB._42 = p->m_pos.y;
//			mBB._43 = p->m_pos.z;
//			break;
//		case eSpherical:
//			mBB._41 = p->m_pos.x * cosf(D3DXToRadian(p->m_pos.z)) * cosf(D3DXToRadian(p->m_pos.y));
//			mBB._42 = p->m_pos.x * cosf(D3DXToRadian(p->m_pos.y));
//			mBB._43 = p->m_pos.x * sinf(D3DXToRadian(p->m_pos.z)) * cosf(D3DXToRadian(p->m_pos.y));
//			break;
//		case eCylindrical:
//			mBB._41 = p->m_pos.x * cosf(D3DXToRadian(p->m_pos.z));
//			mBB._42 = p->m_pos.y;
//			mBB._43 = p->m_pos.x * sinf(D3DXToRadian(p->m_pos.z));
//			break;
//		}
//		mtx = mRZ * mBB;
//		D3DXVECTOR3 pos;
//		D3DXVec3TransformCoord(&pos, &D3DXVECTOR3(p->m_size * -0.5f, p->m_size * 0.5f, 0.0f), &mtx);
//		pV[0].m_pos = pos;
//		D3DXVec3TransformNormal(&pos, &D3DXVECTOR3(0.0f, 0.0f, -1.0f), &mtx);
//		pV[0].m_normal = pos;
//		pV[0].m_diffuse = p->m_color;
//		pV[0].m_u = 0.0f, pV[0].m_v = 0.0f;
//		D3DXVec3TransformCoord(&pos, &D3DXVECTOR3(p->m_size * 0.5f, p->m_size * 0.5f, 0.0f), &mtx);
//		pV[1].m_pos = pos;
//		pV[1].m_normal = pV[0].m_normal;
//		pV[1].m_diffuse = p->m_color;
//		pV[1].m_u = 1.0f, pV[1].m_v = 0.0f;
//		D3DXVec3TransformCoord(&pos, &D3DXVECTOR3(p->m_size * -0.5f, p->m_size * -0.5f, 0.0f), &mtx);
//		pV[2].m_pos = pos;
//		pV[2].m_normal = pV[0].m_normal;
//		pV[2].m_diffuse = p->m_color;
//		pV[2].m_u = 0.0f, pV[2].m_v = 1.0f;
//		D3DXVec3TransformCoord(&pos, &D3DXVECTOR3(p->m_size * 0.5f, p->m_size * -0.5f, 0.0f), &mtx);
//		pV[3].m_pos = pos;
//		pV[3].m_normal = pV[0].m_normal;
//		pV[3].m_diffuse = p->m_color;
//		pV[3].m_u = 1.0f, pV[3].m_v = 1.0f;
//		pV += 4;
//		// �C���f�b�N�X�\�z
//		pI[0] = wIndex + 0;
//		pI[1] = wIndex + 1;
//		pI[2] = wIndex + 2;
//		pI[3] = wIndex + 2;
//		pI[4] = wIndex + 1;
//		pI[5] = wIndex + 3;
//		pI += 6;
//		wIndex += 4;
//	}
//
//	// ���Ԃ�i�߂�
//	m_fTime += fDeltaTime;
//	if (m_fTime >= m_pp.fDuration) {
//		m_fRate = 0.0f;
//		if (m_pp.bLooping) {
//			m_fTime = 0.0f;
//			m_uParticles = m_pp.uMaxParticles;
//		} else {
//			m_fTime = m_pp.fDuration;
//			m_uParticles = 0;
//		}
//	}
//}
//
//void CParticle::LateDraw(void)
//{
//	if (!m_uUse) {
//		return;
//	}
//
//	LPDIRECT3DDEVICE9 pDevice = CWindow::Instance()->GetDevice();
//	D3DXMATRIX mWorld;
//	D3DXMatrixIdentity(&mWorld);
//	pDevice->SetTransform(D3DTS_WORLD, &mWorld);
//
//
//	pDevice->SetFVF(FVF_PVERTEX);
//	const D3DMATERIAL9 material = {
//		{ 1.0f, 1.0f, 1.0f, 1.0f },
//		{ 1.0f, 1.0f, 1.0f, 1.0f },
//		{ 0.1f, 0.1f, 0.1f, 1.0f },
//		{ 0.0f, 0.0f, 0.0f, 1.0f },
//		0.0f,
//	};
//	pDevice->SetMaterial(&material);
//	pDevice->SetTexture(0, m_pTexture);									// �e�N�X�`����o�^
//
//	pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,
//		0, m_uUse * 6, m_uUse * 2, m_pIndex, D3DFMT_INDEX16,
//		m_pVertex, sizeof(*m_pVertex));
//}
//
//void CParticle::SetPos(D3DXVECTOR3 pos)
//{
//	m_mtxWorld._41 = pos.x;
//	m_mtxWorld._42 = pos.y;
//	m_mtxWorld._43 = pos.z;
//}
//
//D3DXVECTOR3 CParticle::GetPos()
//{
//	return D3DXVECTOR3(m_mtxWorld._41,m_mtxWorld._42, m_mtxWorld._43);
//}					   