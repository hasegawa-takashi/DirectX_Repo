//#pragma once
//#include "Camera.h"
//#include"ObjManager.h"
//
//enum EParticleCoord {
//	eCartesian = 0,				// �������W�n(x,y,z)
//	eSpherical,					// �����W�n(r,��,��)
//	eCylindrical,				// �~�����W�n(r,h,��)
//
//	eMaxParticleCoord
//};
//
//struct TParticleParam
//{
//	EParticleCoord	coord;					// ���W�n
//	float			fDuration;				// ��������
//	UINT			uMaxParticles;			// �ő�p�[�e�B�N����
//	bool			bLooping;				// �J��Ԃ�
//	bool			bUse;					// ON/OFF
//	float			fGravity;				// �d�͉����x
//	float			fLowSpeed;				// �Œᑬ�x
//	float			fMaxSpeed;				// �ō����x
//	float			fAccelerator;			// �����x
//	float			fMiniSize;				// �Œ�g�嗦
//	float			fMaxSize;				// �ő�g�嗦
//	float			fLowRotate;				// �Œ�p�x
//	float			fMaxRotate;				// �ő�p�x
//	D3DXCOLOR		LowColor;				// �����J���[
//	D3DXCOLOR		MaxColor;				// �ω���̐F
//	float			fMiniLife;				// �Œ჉�C�t
//	float			fMaxLife;				// �ő僉�C�t
//	UINT			uRate;					// �p�[�e�B�N���̐�����
//	float			fCornAngle;				// �R�[���p�x
//	float			fRadius;				// ���a
//	TCHAR			szTexFName[_MAX_PATH];	// �e�N�X�`���t�@�C����
//};
//
//class CParticle: public ObjBase
//{
//private:
//	LPDIRECT3DTEXTURE9	m_pTexture;
//	TCHAR				m_szTexFName[_MAX_PATH];	// �e�N�X�`���t�@�C����
//
//	TParticleParam		m_pp;
//	float				m_fTime;			// �p�[�e�B�N����������
//	float				m_fRate;			// �p�[�e�B�N�����������[�N
//	UINT				m_uParticles;		// �c��p�[�e�B�N����
//
//	UINT		m_uUse;
//	struct TVertex {
//		D3DVECTOR	m_pos;
//		D3DVECTOR	m_normal;
//		D3DCOLOR	m_diffuse;
//		float		m_u, m_v;
//	};
//	TVertex*	m_pVertex;
//	WORD*		m_pIndex;
//
//public:
//	void SetParam(TParticleParam& pp);
//
//	//===================================
//	//
//	//		���������A�p����
//	//
//	CParticle();				// �R���X�g���N�^
//	virtual ~CParticle(void);	// �f�X�g���N�^//
//
//	void Init();				// ������
//	void Update();				// �X�V
//	void LateUpdate() {}		// ���Ƃ���X�V
//	void Draw();				// �`��
//	void LateDraw();			// ���ߕ`��
//	void UIDraw() {}			// UI�`��
//	void Release();				// �����[�X
//	void Pause() {}				// �|�[�Y���
//	bool AllRelaseObj() {}		// �I���p
//
//	ColBox GetCol() { return Collision; }
//	CMeshRender* GetRender() { return m_ModelMesh; }
//	void SetidentNumb(int Numb) { ObjNumb = Numb; }
//	void SetPos(D3DXVECTOR3 pos);
//	virtual D3DXVECTOR3 GetPos() { return m_Pos; }
//
//private:
//	void UpdateTexture(void);
//
//	//===================================
//	//
//	//		�v���C�x�[�g�ϐ�
//	//
//	ColBox Collision;			// �����蔻��p
//
//};