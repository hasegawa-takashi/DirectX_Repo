#pragma once

#include"ObjManager.h"
#include"Window.h"



#define VECZERO D3DXVECTOR3(0,0,0)
//////////////////////////////////
//		���݂̃J�����̏��
//////////////////////////////////
enum CamState
{
	Cam_FPVIEW = 0,
	Cam_TPVIEW,
	Cam_PREVIEW,

	MAX_VIEW
};

//////////////////////////////////////////////////////////////
//
//		Camara
//			�Q�[�����J�����̃N���X
//				���ʃJ������FPS�J���������Ȃ��Ⴂ���Ȃ����ƂɋC�t����
//
/////////////////////////////////////////////////////////////

class CCamera : public ObjBase
{

public:

	//---------------------------------------
	// �J�����̃f�X�g���N�^
	~CCamera();

	//---------------------------------------
	// �J�����̃R���X�g���N�^
	CCamera();

	//---------------------------------------
	// �J�����̃C���X�^���X
	/*static CCamera* Instance(){
		static CCamera _Instance;
		return &_Instance;
	}*/

	//----------------------------
	// --- �I�u�W�F�N�g�̏�����
	void Init();
	//----------------------------
	// --- �I�u�W�F�N�g�̍X�V
	void Update();
	//----------------------------
	// --- �I�u�W�F�N�g�̕`��
	void Draw();
	//----------------------------
	// --- �I�u�W�F�N�g�̍폜
	void Release();
	//----------------------------
	// --- �|�[�Y���
	void Pause(){};
	//----------------------------
	// --- �\�����
	void UIDraw(){};
	//----------------------------
	// --- �ŏI�����S�폜�p
	bool AllRelaseObj(){ return true; };

	//---------------------------------------
	// �J�����̍��W�̎擾
	D3DXVECTOR3 GetCameraPos();

	//---------------------------------------
	// �J�����̌���
	D3DXMATRIX GetCameraView()
	{
		return m_mtxView;
	}

	//---------------------------------------
	// �J�����̈ړ��X�V
	void CameraMove();
	
	//---------------------------------------
	// �J�����̒����_�̐ݒ�
	void SetLookAt(D3DXVECTOR3 look);

	//---------------------------------------
	// �J������Z��]
	void RotZ(float radian);

	//----------------------------------------
	// --- �I�u�W�F�N�g�̍X�V(���Ƃ���p)
	void LateUpdate();

	//----------------------------------------
	// --- �I�u�W�F�N�g�̕`��(���Ƃ���p)
	void LateDraw();

	//----------------------------------------
	// --- �R���W�����̐ݒ�
	ColBox GetCol();

	//----------------------------------------
	// --- View�s��̎擾
	D3DXVECTOR3 GetView();

	//----------------------------------------
	// --- �J�����^�C�v�̐ݒ�
	void SetCameraType(int Type);

	//----------------------------------------
	// --- Pos�̎擾
	void SetPos(D3DXVECTOR3 Pos);

private:

	//---------------------------------------
	// FPS�J����
	void FPSCamera();

	//---------------------------------------
	// ���ʑ����J����
	void TPSCamera();

	//---------------------------------------
	// �^�C�g�����̃J�����������Ȃ��p
	void PreviewCamera();

	//---------------------------------------
	// �N�I�[�^�j�I�����s��v�Z
	void QuaternionToMatrix();

	//---------------------------------------
	// �s��v�Z���N�I�[�^�j�I��
	void MatrixToQuaternion();

	//---------------------------------------
	// �x�N�g���Ԃ̊p�x���Z�o
	double AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B);

	// --- ��������ϐ��錾 --- //
	int m_CamType;
	int ObjNumb;
	bool m_isNeedUpdate;			// �X�V�����H

	D3DXVECTOR3 m_OldPos;

	D3DXVECTOR3	m_lookAt;			// �����_
	D3DXVECTOR3 m_Move;				// �ړ�����
	D3DXVECTOR3 m_DirDef;			// �J�����̌���
	D3DXVECTOR3 m_Upvec;			// ��

	D3DXVECTOR3 NowPos;				// ���ݍ��W
	D3DXVECTOR3 NowRot;				// ���݂̉�]�l

	D3DXVECTOR3 m_CameraMove;		// ���x

	D3DXVECTOR3 m_CorrectionVal;	// lookat�̕␳�l

	float m_Distance;				// �J�����ƒ����_�̋���
	float m_camZrot;				// �J����Z���ł̉�]����
	float m_camAngleUnit;			// �ړ����̉�]�P��
	float m_offsetZ;				// �I�t�Z�b�g�l

	float		m_fFovy;	// ����p
	float		m_fAspect;	// �A�X�y�N�g��
	float		m_fZNear;	// �O���N���b�v����
	float		m_fZFar;	// ����N���b�v����

	D3DXMATRIX	m_mtxView;			// �r���[�}�g���N�X
	D3DXMATRIX	m_mtxProjection;	// �v���W�F�N�V�����}�g���N�X
	D3DXMATRIX	m_camPoseMat;		// �J�����̎p���s��

	ColBox Collision;				// �����蔻��p

	OBJMGR Master;



};

