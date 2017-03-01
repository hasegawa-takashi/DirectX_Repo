#pragma once
#include "ObjManager.h"
#include"MeshRender.h"
#include "Window.h"
#include"Billbord.h"
#include"Ballet.h"
#include<vector>
#include"Camera.h"

#define MAX_BALLET (30)

class Player : public ObjBase
{
public:
	//----------------------------
	// --- �R���X�g���N�^
	Player();
	
	//----------------------------
	// --- �f�X�g���N�^
	~Player();

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
	void LateDraw();
	//----------------------------------------
	// --- �I�u�W�F�N�g�̕`��(���Ƃ���p)
	void UIDraw();
	//----------------------------
	// --- �I�u�W�F�N�g�̍폜
	void Release();
	//----------------------------
	// --- �|�[�Y���
	void Pause(){};
	//----------------------------
	// --- �ŏI�����S�폜�p
	bool AllRelaseObj(){ return true; }

	//----------------------------
	// --- �����̎擾
	D3DXVECTOR3 GetDir(){ return m_NowDir; }

	//----------------------------------------
	// --- �Q�[���N���A
	void LastRun();


private:

	// �J�����p�̃I�u�W�F�N
	CCamera *CameraObj;					// �^�L���X�g��̃I�u�W�F�N�g
	OBJMGR CameraObjMgr;				// �^�L���X�g�O�̃I�u�W�F�N�g


	int HitCnt;
	int BalletCnt;						// ���˃o���b�g�̒e��

	float m_Dir;						// �ړ�����
	float m_Rotate;						// �v���C���[�̌���s
	D3DXVECTOR3 m_NowDir;
	D3DXVECTOR3 m_MoveSpeed;			// �������x
	

	float m_Speed;						// �ړ����x
	float m_Dash;						// �_�b�V���ړ����x
	float m_Step;						// �X�e�b�v�X�s�[�h(�����Ƃ�����)

	bool m_Jump;						// �W�����v�t���O
	bool m_Move;						// �ړ��t���O
	bool m_Load;						// ���f���ǂݍ��݃t���O

	float m_dwPrev;						// �o�ߎ��Ԍv���p
	double m_dAnimTime;					// �A�j���[�V��������

	BulletBox balletpram_L;				// L����
	BulletBox balletpram_R;				// R����

	std::vector<CBallet> _vecbullet_L;	// �o���b�g�̃x�N�^�[
	std::vector<CBallet> _vecbullet_R;	// �o���b�g�̃x�N�^�[

	// === ���������private�֐� === //
	void Move();						// �ړ��p
	void Shot();						// �ˌ��p
	void TransBorn();					// �{�[���̔P���Ȃ�
	void ChangeACTDir();				// �����̂��肩���悤
	void ChangeTPSDir();				// �����̂��肩���悤
	void CheckFloor();					// ���Ƃ̔��菈��
	void Reset();
};

