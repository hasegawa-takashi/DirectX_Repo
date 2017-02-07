#pragma once
#include "ObjManager.h"

struct Collison
{
	D3DXVECTOR3 Center;
	D3DXVECTOR3 Box;
	float Width;
	float Height;

};

class CCollision : public CObjManager
{
public:
	//----------------------------
	// --- �R���X�g���N�^
	CCollision();

	//----------------------------
	// --- �f�X�g���N�^
	~CCollision();
	
	//--------------------------------------
	// --- �I�u�W�F�N�g�̌����p+�����
	// --- ������ :: �T���I�u�W�F�N�g��ID
	// --- ������ :: �����̕��@
	bool CollisonCheck(UINT ID , int Colltype );

	//----------------------------
	// --- ���̔���
	bool CollisionBSphere(ObjBase* pObj, UINT ID);

	//----------------------------
	// --- AABB����
	bool CollisionAABB(ObjBase* pObj, UINT ID);

	//----------------------------
	// --- OBB����
	bool CollisionOBB(ObjBase* pObj, UINT ID);

};

