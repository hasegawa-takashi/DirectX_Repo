#pragma once

#include<d3dx9.h>

#include"ObjMgr.h"
class ObjBase;

class ColBox {


public:
	ColBox(ObjBase* thisobj);
	~ColBox() {}
	
	// OBB判定
	D3DXVECTOR3 m_Pos;              // 位置
	D3DXVECTOR3 m_NormaDirect[3];   // 方向ベクトル
	FLOAT m_fLength[3];             // 各軸方向の長さ
	float Radius;					// 半径
	D3DXMATRIX WorldMtx;			// ワールドマトリクスs
	D3DXVECTOR3 Ray;				// レイの方向
	D3DXVECTOR3 ResultPos;			// 交差地点の結果を取得
	ObjBase* ThisObj;				// これを保有しているobj
};

#include"includeheader.h"

class CRenderModel;
#include"RenderModel.h"

enum CollisionType
{
	COL_SPHERE = 0,		// 球::球
	COL_AABB,		// AABB::AABB 未完成
	COL_OBB,		// OBB::OBB
	COL_RAY,		// RAY::MESH
	COL_RAY_SPHERE,	// RAY::球
	COL_RAY_OBB,	// RAY::OBB 未完成
	MAX_COL
};

//////////////////////////////////////////////////////////////
//
//		ColBox
//			検索の関係上ここに描く。
//			当たり判定を持たせるオブジェクトには保持させること
//
/////////////////////////////////////////////////////////////

class CCollisionMgr
{
public:
	std::list<ObjBase*> CheckHitObj(ColBox* thisObj , CollisionType type,int name, CRenderModel* modelMesh = nullptr);
	void SetCollision(ColBox *obj);
	void DeleteCollision(ColBox *obj);

private:

	std::list<ColBox*> m_Collisionlist; // オブジェクトの登録

	float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3=0);
	std::list<ObjBase*> Sphere(ColBox* thisObj);		// 球面
	std::list<ObjBase*> OBB(ColBox* thisObj);			// OBB
	std::list<ObjBase*> RaySphere(ColBox* thisObj);	// レイと球
	std::list<ObjBase*> Raycast(ColBox* thisObj, CRenderModel* modelMesh);		// レイ
};