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
	// --- コンストラクタ
	CCollision();

	//----------------------------
	// --- デストラクタ
	~CCollision();
	
	//--------------------------------------
	// --- オブジェクトの検索用+判定も
	// --- 第一引数 :: 探すオブジェクトのID
	// --- 第二引数 :: 検索の方法
	bool CollisonCheck(UINT ID , int Colltype );

	//----------------------------
	// --- 球体判定
	bool CollisionBSphere(ObjBase* pObj, UINT ID);

	//----------------------------
	// --- AABB判定
	bool CollisionAABB(ObjBase* pObj, UINT ID);

	//----------------------------
	// --- OBB判定
	bool CollisionOBB(ObjBase* pObj, UINT ID);

};

