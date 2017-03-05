#pragma once
#include "ObjManager.h"



enum CollisionType
{
	COL_SPHERE,		// 球::球
	COL_AABB,		// AABB::AABB
	COL_OBB,		// OBB::OBB
	COL_RAY,		// RAY::MESH
	COL_RAY_SPHERE,	// RAY::球
	COL_RAY_OBB,	// RAY::OBB
	MAX_COL
};

//////////////////////////////////////////////////////////////
//
//		ColBox
//			検索の関係上ここに描く。
//			当たり判定を持たせるオブジェクトには保持させること
//
/////////////////////////////////////////////////////////////
class ColBox {

public:
	// OBB判定
	D3DXVECTOR3 m_Pos;              // 位置
	D3DXVECTOR3 m_NormaDirect[3];   // 方向ベクトル
	FLOAT m_fLength[3];             // 各軸方向の長さ
	float Radius;					// 半径
	D3DXMATRIX WorldMtx;			// ワールドマトリクスs
	D3DXVECTOR3 Ray;				// レイの方向
	D3DXVECTOR3 ResultPos;			// 交差地点の結果を取得
	int m_SetObjId;					// 対象のメッシュ
	int IdentNumb;					// 固有ナンバー

	std::multimap<int, int> Obj;	// オブジェクトの固有番号

};



class CCollision 
{
public:
	//----------------------------
	// --- コンストラクタ
	CCollision();

	//----------------------------
	// --- デストラクタ
	~CCollision();
	
	// === ここから先当たり判定関係 === //
	// === 上手い作り方がわからなかったのでここで一括で当たり判定を構成 === //

	//--------------------------------------
	// --- オブジェクトの検索用+判定も
	// --- 第一引数 :: 探すオブジェクトのID
	// --- 第二引数 :: 検索の方法
	bool CollisonCheck(UINT ID, int Colltype, ColBox &obb1);
	float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0);

	//---------------------------
	// --- OBBの引っ張ってくる設定
	ColBox GetCol() {};

private:

	//----------------------------
	// --- 球体判定
	bool CollisionBSphere(ColBox &obb1, ColBox &obb2);

	//----------------------------
	// --- AABB判定
	bool CollisionAABB(ObjBase* pObj, UINT ID);

	//----------------------------
	// --- OBB判定
	bool CollisionOBB(ColBox &obb1, ColBox &obb2);

	//----------------------------
	// --- Ray+Spher
	bool calcRaySphere(ColBox &obb1, ColBox &obb2);


};

