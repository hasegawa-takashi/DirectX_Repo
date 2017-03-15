#pragma once

#include"Window.h"
#include"ObjManager.h"
#include"MeshRender.h"
#include"Billbord.h"


struct BulletBox
{
	float fSpeed;			// �e�̑��x
	D3DXVECTOR3 Dir;		// �e�̌���
	D3DXVECTOR3 Pos;		// �e�̃|�W�V����
	float Length;			// �e�̔��ˋ���
	float SwingRange;		// �G�C���̃u����
	int BalletType;			// �e�̎��
};

enum Ballet_Type{

	MAX_BULLET_TYPE
};

class CBallet : public ObjBase
{
public:
	CBallet();
	~CBallet();

	//----------------------------
	// --- �I�u�W�F�N�g�̏�����
	void Init();
	//----------------------------
	// --- �I�u�W�F�N�g�̍X�V
	void Update();
	//----------------------------
	// --- �I�u�W�F�N�g�̍X�V(���Ƃ���p)
	void LateUpdate(){};
	//----------------------------
	// --- �I�u�W�F�N�g�̕`��
	void Draw();
	//----------------------------------------
	// --- �I�u�W�F�N�g�̕`��(���Ƃ���p)
	void LateDraw(){};
	void UIDraw(){};
	//----------------------------
	// --- �I�u�W�F�N�g�̍폜
	void Release();
	//----------------------------
	// --- �|�[�Y���
	void Pause(){};
	//----------------------------
	// --- �ŏI�����S�폜�p
	bool AllRelaseObj(){ return true; };


	//----------------------------------------
	// --- Reload
	void Reload(){ ShotFlag = false; }

	bool GetShotFlag(){ return ShotFlag; }

	bool GetHitCheck();

	//----------------------------------------
	// --- �e�̐���
	// --- �e�̏����������\���̂����āA�ǂ���
	bool CreateBallet(BulletBox bullet);

private:
	

	float m_Range;				// �e�̍ő勗��
	D3DXVECTOR3 m_Dir;			// �e�̌���
	bool ShotFlag;				// �e��������?(Y/N)

	float m_MaxError;			// �u���͈̔�

	bool m_Load;				// ���f���ǂݍ��݃t���O
	
	bool Hitflag;

};

