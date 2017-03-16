#pragma once

#include"ObjManager.h"

#include<d3dx9.h>
#include<list>
#include<map>

// 前方宣言
class ObjBase;
class CMeshRender;
// コリジョンの判定の種類別前方宣言
class Sphere;
class AABB;
class OBB;
class RaySphere;
class Raycast;

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
struct ColBox {

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


//////////////////////////////////////////////////////////////
//
//		CCollision
//			判定の呼び出し用
//
/////////////////////////////////////////////////////////////
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


	virtual std::list<ObjBase*> ISCollision(const Sphere*) = 0;
	virtual std::list<ObjBase*> ISCollision(const AABB*) = 0;
	virtual std::list<ObjBase*> ISCollision(const OBB*) = 0;
	virtual std::list<ObjBase*> ISCollision(const RaySphere*) = 0;
	virtual std::list<ObjBase*> ISCollision(const Raycast*) = 0;

	//--------------------------------------
	// --- オブジェクトの検索用+判定も
	// --- 第一引数 :: 探すオブジェクトのID
	// --- 第二引数 :: 検索の方法
	//bool CollisonCheck(UINT ID, int Colltype, ColBox &obb1);

	//---------------------------
	// --- OBBの引っ張ってくる設定
	//ColBox GetCol() {};

protected:

	std::list<ObjBase*> m_TargetObjList;	// 対象オブジェクト用
	std::list<ObjBase*> m_ReturnTargetObjList;
	CMeshRender *m_ModelMesh;	// 描画用の変数クラス

private:

};

//////////////////////////////////////////////////////////////
//
//		Sphere
//			球体の当たり判定用
//
/////////////////////////////////////////////////////////////
class Sphere : public CCollision
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
class AABB : public CCollision
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
class OBB : public CCollision
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
class RaySphere : public CCollision
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
class Raycast : public CCollision
{
public:
	Raycast() {};
	~Raycast() {};

	//----------------------------
	// --- 球体判定
	std::list<ObjBase*> ISCollision(ColBox &obb1, UINT ID);
};


