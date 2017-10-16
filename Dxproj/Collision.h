#pragma once

#include<d3dx9.h>

#include"ObjMgr.h"
class ObjBase;

class ColBox {


public:
	ColBox(ObjBase* thisobj);
	~ColBox() {}
	
	// OBB����
	D3DXVECTOR3 m_Pos;              // �ʒu
	D3DXVECTOR3 m_NormaDirect[3];   // �����x�N�g��
	FLOAT m_fLength[3];             // �e�������̒���
	float Radius;					// ���a
	D3DXMATRIX WorldMtx;			// ���[���h�}�g���N�Xs
	D3DXVECTOR3 Ray;				// ���C�̕���
	D3DXVECTOR3 ResultPos;			// �����n�_�̌��ʂ��擾
	ObjBase* ThisObj;				// �����ۗL���Ă���obj
};

#include"includeheader.h"

class CRenderModel;
#include"RenderModel.h"

enum CollisionType
{
	COL_SPHERE = 0,		// ��::��
	COL_AABB,		// AABB::AABB ������
	COL_OBB,		// OBB::OBB
	COL_RAY,		// RAY::MESH
	COL_RAY_SPHERE,	// RAY::��
	COL_RAY_OBB,	// RAY::OBB ������
	MAX_COL
};

//////////////////////////////////////////////////////////////
//
//		ColBox
//			�����̊֌W�ケ���ɕ`���B
//			�����蔻�����������I�u�W�F�N�g�ɂ͕ێ������邱��
//
/////////////////////////////////////////////////////////////

class CCollisionMgr
{
public:
	std::list<ObjBase*> CheckHitObj(ColBox* thisObj , CollisionType type,int name, CRenderModel* modelMesh = nullptr);
	void SetCollision(ColBox *obj);
	void DeleteCollision(ColBox *obj);

private:

	std::list<ColBox*> m_Collisionlist; // �I�u�W�F�N�g�̓o�^

	float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3=0);
	std::list<ObjBase*> Sphere(ColBox* thisObj);		// ����
	std::list<ObjBase*> OBB(ColBox* thisObj);			// OBB
	std::list<ObjBase*> RaySphere(ColBox* thisObj);	// ���C�Ƌ�
	std::list<ObjBase*> Raycast(ColBox* thisObj, CRenderModel* modelMesh);		// ���C
};