#pragma once
#include "ObjManager.h"



enum CollisionType
{
	COL_SPHERE,		// ��::��
	COL_AABB,		// AABB::AABB
	COL_OBB,		// OBB::OBB
	COL_RAY,		// RAY::MESH
	COL_RAY_SPHERE,	// RAY::��
	COL_RAY_OBB,	// RAY::OBB
	MAX_COL
};

//////////////////////////////////////////////////////////////
//
//		ColBox
//			�����̊֌W�ケ���ɕ`���B
//			�����蔻�����������I�u�W�F�N�g�ɂ͕ێ������邱��
//
/////////////////////////////////////////////////////////////
class ColBox {

public:
	// OBB����
	D3DXVECTOR3 m_Pos;              // �ʒu
	D3DXVECTOR3 m_NormaDirect[3];   // �����x�N�g��
	FLOAT m_fLength[3];             // �e�������̒���
	float Radius;					// ���a
	D3DXMATRIX WorldMtx;			// ���[���h�}�g���N�Xs
	D3DXVECTOR3 Ray;				// ���C�̕���
	D3DXVECTOR3 ResultPos;			// �����n�_�̌��ʂ��擾
	int m_SetObjId;					// �Ώۂ̃��b�V��
	int IdentNumb;					// �ŗL�i���o�[

	std::multimap<int, int> Obj;	// �I�u�W�F�N�g�̌ŗL�ԍ�

};



class CCollision 
{
public:
	//----------------------------
	// --- �R���X�g���N�^
	CCollision();

	//----------------------------
	// --- �f�X�g���N�^
	~CCollision();
	
	// === ��������擖���蔻��֌W === //
	// === ��肢�������킩��Ȃ������̂ł����ňꊇ�œ����蔻����\�� === //

	//--------------------------------------
	// --- �I�u�W�F�N�g�̌����p+�����
	// --- ������ :: �T���I�u�W�F�N�g��ID
	// --- ������ :: �����̕��@
	bool CollisonCheck(UINT ID, int Colltype, ColBox &obb1);
	float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0);

	//---------------------------
	// --- OBB�̈��������Ă���ݒ�
	ColBox GetCol() {};

private:

	//----------------------------
	// --- ���̔���
	bool CollisionBSphere(ColBox &obb1, ColBox &obb2);

	//----------------------------
	// --- AABB����
	bool CollisionAABB(ObjBase* pObj, UINT ID);

	//----------------------------
	// --- OBB����
	bool CollisionOBB(ColBox &obb1, ColBox &obb2);

	//----------------------------
	// --- Ray+Spher
	bool calcRaySphere(ColBox &obb1, ColBox &obb2);


};

