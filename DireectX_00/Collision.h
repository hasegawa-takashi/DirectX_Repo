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


//////////////////////////////////////////////////////////////
//
//		CCollision
//			����̌Ăяo���p
//
/////////////////////////////////////////////////////////////
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


	virtual list<ObjBase*> ISCollision(const Sphere*) = 0;
	virtual list<ObjBase*> ISCollision(const AABB*) = 0;
	virtual list<ObjBase*> ISCollision(const OBB*) = 0;
	virtual list<ObjBase*> ISCollision(const RaySphere*) = 0;
	virtual list<ObjBase*> ISCollision(const Raycast*) = 0;

	//--------------------------------------
	// --- �I�u�W�F�N�g�̌����p+�����
	// --- ������ :: �T���I�u�W�F�N�g��ID
	// --- ������ :: �����̕��@
	//bool CollisonCheck(UINT ID, int Colltype, ColBox &obb1);
	
	//---------------------------
	// --- OBB�̈��������Ă���ݒ�
	//ColBox GetCol() {};

protected:

	list<ObjBase*> m_TargetObjList;	// �ΏۃI�u�W�F�N�g�p
	list<ObjBase*> m_ReturnTargetObjList;
	CMeshRender *m_ModelMesh;	// �`��p�̕ϐ��N���X

private:
	
};

//////////////////////////////////////////////////////////////
//
//		Sphere
//			���̂̓����蔻��p
//
/////////////////////////////////////////////////////////////
class Sphere : public CCollision
{
public:
	Sphere() {};
	~Sphere() {};

	//----------------------------
	// --- ���̔���
	list<ObjBase*> ISCollision(ColBox &obb1, UINT ID);
};

//////////////////////////////////////////////////////////////
//
//		AABB
//			�Œ��`�̓����蔻��
//
/////////////////////////////////////////////////////////////
class AABB : public CCollision
{
public:
	AABB() {};
	~AABB() {};

	//----------------------------
	// --- AABB����
	list<ObjBase*> ISCollision(ColBox &obb1, UINT ID);
};

//////////////////////////////////////////////////////////////
//
//		OBB
//			��]��`�̓����蔻��
//
/////////////////////////////////////////////////////////////
class OBB : public CCollision
{
public:
	OBB() {};
	~OBB() {};

	list<ObjBase*> ISCollision(ColBox &obb1, UINT ID);

private:
	float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0);

};

//////////////////////////////////////////////////////////////
//
//		RaySphere
//			Ray�Ƌ��̓����蔻��
//
/////////////////////////////////////////////////////////////
class RaySphere : public CCollision
{
public:
	RaySphere() {};
	~RaySphere() {};

	list<ObjBase*> ISCollision(ColBox &obb1, UINT ID);
};

//////////////////////////////////////////////////////////////
//
//		Sphere
//			���̂̓����蔻��p
//
/////////////////////////////////////////////////////////////
class Raycast : public CCollision
{
public:
	Raycast() {};
	~Raycast() {};

	//----------------------------
	// --- ���̔���
	list<ObjBase*> ISCollision(ColBox &obb1, UINT ID);
};