#pragma once
#include"includeheader.h"
#include"Collision.h"

//////////////////////////////////////////////////////////////
//
//		Sphere
//			���̂̓����蔻��p
//
/////////////////////////////////////////////////////////////
static class Sphere
{
public:
	Sphere() {};
	~Sphere() {};

	//----------------------------
	// --- ���̔���
	std::list<ObjBase*> ISCollision(ColBox &obb1, UINT ID);
};

//////////////////////////////////////////////////////////////
//
//		AABB
//			�Œ��`�̓����蔻��
//
/////////////////////////////////////////////////////////////
static class AABB
{
public:
	AABB() {};
	~AABB() {};

	//----------------------------
	// --- AABB����
	std::list<ObjBase*> ISCollision(ColBox &obb1, UINT ID);
};

//////////////////////////////////////////////////////////////
//
//		OBB
//			��]��`�̓����蔻��
//
/////////////////////////////////////////////////////////////
static class OBB
{
public:
	OBB() {};
	~OBB() {};

	std::list<ObjBase*> ISCollision(ColBox &obb1, UINT ID);

private:
	float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0);

};

//////////////////////////////////////////////////////////////
//
//		RaySphere
//			Ray�Ƌ��̓����蔻��
//
/////////////////////////////////////////////////////////////
static class RaySphere
{
public:
	RaySphere() {};
	~RaySphere() {};

	std::list<ObjBase*> ISCollision(ColBox &obb1, UINT ID);
};

//////////////////////////////////////////////////////////////
//
//		Sphere
//			���̂̓����蔻��p
//
/////////////////////////////////////////////////////////////
static class Raycast
{
public:
	Raycast() {};
	~Raycast() {};

	//----------------------------
	// --- ���̔���
	std::list<ObjBase*> ISCollision(ColBox &obb1, UINT ID);
};


