#pragma once
#include"includeheader.h"
#include"Collision.h"

//////////////////////////////////////////////////////////////
//
//		Sphere
//			球体の当たり判定用
//
/////////////////////////////////////////////////////////////
static class Sphere
{
public:
	Sphere() {};
	~Sphere() {};

	//----------------------------
	// --- 球体判定
	std::list<ObjBase*> ISCollision(ColBox &obb1, UINT ID);
};

//////////////////////////////////////////////////////////////
//
//		AABB
//			固定矩形の当たり判定
//
/////////////////////////////////////////////////////////////
static class AABB
{
public:
	AABB() {};
	~AABB() {};

	//----------------------------
	// --- AABB判定
	std::list<ObjBase*> ISCollision(ColBox &obb1, UINT ID);
};

//////////////////////////////////////////////////////////////
//
//		OBB
//			回転矩形の当たり判定
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
//			Rayと球の当たり判定
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
//			球体の当たり判定用
//
/////////////////////////////////////////////////////////////
static class Raycast
{
public:
	Raycast() {};
	~Raycast() {};

	//----------------------------
	// --- 球体判定
	std::list<ObjBase*> ISCollision(ColBox &obb1, UINT ID);
};


