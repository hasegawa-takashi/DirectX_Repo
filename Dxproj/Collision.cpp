#include "Collision.h"

ColBox::ColBox(ObjBase* thisobj)
{
	ThisObj = thisobj;
}

CCollisionMgr::CCollisionMgr()
{
	m_Collisionlist.clear();
}

CCollisionMgr::~CCollisionMgr()
{
	
}

void CCollisionMgr::ResetCollisionList()
{
	m_Collisionlist.clear();
}

/// <summary>
/// コリジョンの窓口
/// </summary>
/// <param name="type"></param>
/// <param name="name"></param>
/// <returns></returns>
std::list<ObjBase*> CCollisionMgr::CheckHitObj(ColBox* thisObj ,CollisionType type)
{
	std::list<ObjBase*> _ReturnTargetObjList;

	switch (type)
	{
	case COL_SPHERE:
		_ReturnTargetObjList = Sphere(thisObj);
		break;
	case COL_AABB:
		break;
	case COL_OBB:
		_ReturnTargetObjList = OBB(thisObj);
		break;
	case COL_RAY:
		_ReturnTargetObjList = Raycast(thisObj);
		break;
	case COL_RAY_SPHERE:
		_ReturnTargetObjList = RaySphere(thisObj);
		break;
	case COL_RAY_OBB:
		break;
	case MAX_COL:
		break;
	default:
		break;
	}

	return _ReturnTargetObjList;

}


void CCollisionMgr::SetCollision(ColBox *obj)
{
	m_Collisionlist.push_back(obj);
}

void CCollisionMgr::DeleteCollision(ColBox *obj)
{
	m_Collisionlist.remove(obj);
}

std::list<ObjBase*> CCollisionMgr::Sphere(ColBox* thisObj)
{
	std::list<ObjBase*> _ReturnTargetObjList;

	for (auto& p : m_Collisionlist)
	{
		if (p == thisObj)
			continue;

		if ((powf(thisObj->m_Pos.x - p->m_Pos.x, 2.0f) + powf(thisObj->m_Pos.y - p->m_Pos.y, 2.0f) + powf((thisObj->m_Pos.z - p->m_Pos.z), 2) <= powf((thisObj->Radius + p->Radius), 2)))
		{
			_ReturnTargetObjList.push_back(p->ThisObj);
		}
	}

	return _ReturnTargetObjList;
}

std::list<ObjBase*> CCollisionMgr::OBB(ColBox* thisObj)
{
	std::list<ObjBase*> _ReturnTargetObjList;

	for (auto& p : m_Collisionlist)
	{
		if (p == thisObj)
			continue;

		// 各方向ベクトルの確保
		// （N***:標準化方向ベクトル）
		D3DXVECTOR3 Norma1_X;
		D3DXVECTOR3 Norma1_Y;
		D3DXVECTOR3 Norma1_Z;

		D3DXVECTOR3 Norma2_X;
		D3DXVECTOR3 Norma2_Y;
		D3DXVECTOR3 Norma2_Z;

		Norma1_X.x = thisObj->WorldMtx._11;
		Norma1_X.y = thisObj->WorldMtx._12;
		Norma1_X.z = thisObj->WorldMtx._13;

		Norma1_Y.x = thisObj->WorldMtx._21;
		Norma1_Y.y = thisObj->WorldMtx._22;
		Norma1_Y.z = thisObj->WorldMtx._23;

		Norma1_Z.x = thisObj->WorldMtx._31;
		Norma1_Z.y = thisObj->WorldMtx._32;
		Norma1_Z.z = thisObj->WorldMtx._33;

		Norma2_X.x = p->WorldMtx._11;
		Norma2_X.y = p->WorldMtx._12;
		Norma2_X.z = p->WorldMtx._13;
					 
		Norma2_Y.x = p->WorldMtx._21;
		Norma2_Y.y = p->WorldMtx._22;
		Norma2_Y.z = p->WorldMtx._23;
					 
		Norma2_Z.x = p->WorldMtx._31;
		Norma2_Z.y = p->WorldMtx._32;
		Norma2_Z.z = p->WorldMtx._33;

		D3DXVECTOR3 NAe1 = Norma1_X, Ae1 = NAe1 * thisObj->m_fLength[0];
		D3DXVECTOR3 NAe2 = Norma1_Y, Ae2 = NAe2 * thisObj->m_fLength[1];
		D3DXVECTOR3 NAe3 = Norma1_Z, Ae3 = NAe3 * thisObj->m_fLength[2];
		D3DXVECTOR3 NBe1 = Norma2_X, Be1 = NBe1 * p->m_fLength[0];
		D3DXVECTOR3 NBe2 = Norma2_Y, Be2 = NBe2 * p->m_fLength[1];
		D3DXVECTOR3 NBe3 = Norma2_Z, Be3 = NBe3 * p->m_fLength[2];
		D3DXVECTOR3 Interval = thisObj->m_Pos - p->m_Pos;

		// 分離軸 : Ae1
		FLOAT rA = D3DXVec3Length(&Ae1);
		FLOAT rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
		FLOAT L = fabs(D3DXVec3Dot(&Interval, &NAe1));
		if (L > rA + rB)
			continue; // 衝突していない

					  // 分離軸 : Ae2
		rA = D3DXVec3Length(&Ae2);
		rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &NAe2));
		if (L > rA + rB)
			continue;

		// 分離軸 : Ae3
		rA = D3DXVec3Length(&Ae3);
		rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &NAe3));
		if (L > rA + rB)
			continue;

		// 分離軸 : Be1
		rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
		rB = D3DXVec3Length(&Be1);
		L = fabs(D3DXVec3Dot(&Interval, &NBe1));
		if (L > rA + rB)
			continue;

		// 分離軸 : Be2
		rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
		rB = D3DXVec3Length(&Be2);
		L = fabs(D3DXVec3Dot(&Interval, &NBe2));
		if (L > rA + rB)
			continue;

		// 分離軸 : Be3
		rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
		rB = D3DXVec3Length(&Be3);
		L = fabs(D3DXVec3Dot(&Interval, &NBe3));
		if (L > rA + rB)
			continue;

		// 分離軸 : C11
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &NAe1, &NBe1);
		rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// 分離軸 : C12
		D3DXVec3Cross(&Cross, &NAe1, &NBe2);
		rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// 分離軸 : C13
		D3DXVec3Cross(&Cross, &NAe1, &NBe3);
		rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// 分離軸 : C21
		D3DXVec3Cross(&Cross, &NAe2, &NBe1);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// 分離軸 : C22
		D3DXVec3Cross(&Cross, &NAe2, &NBe2);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// 分離軸 : C23
		D3DXVec3Cross(&Cross, &NAe2, &NBe3);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// 分離軸 : C31
		D3DXVec3Cross(&Cross, &NAe3, &NBe1);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
		rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// 分離軸 : C32
		D3DXVec3Cross(&Cross, &NAe3, &NBe2);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// 分離軸 : C33
		D3DXVec3Cross(&Cross, &NAe3, &NBe3);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// 分離平面が存在しないので「衝突している」
		_ReturnTargetObjList.push_back(p->ThisObj);

	}

	return _ReturnTargetObjList;
}

float CCollisionMgr::LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3)
{
	// 3つの内積の絶対値の和で投影線分長を計算
	// 分離軸Sepは標準化されていること
	float r1 = fabs(D3DXVec3Dot(Sep, e1));
	float r2 = fabs(D3DXVec3Dot(Sep, e2));
	float r3 = e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0;
	return r1 + r2 + r3;
}

std::list<ObjBase*> CCollisionMgr::RaySphere(ColBox* thisObj)
{
	std::list<ObjBase*> _ReturnTargetObjList;

	for (auto& p : m_Collisionlist)
	{
		if (p == thisObj)
			continue;

		float px = p->m_Pos.x - thisObj->m_Pos.x;
		float py = p->m_Pos.y - thisObj->m_Pos.y;
		float pz = p->m_Pos.z - thisObj->m_Pos.z;

		float A = thisObj->Ray.x * thisObj->Ray.x + thisObj->Ray.y * thisObj->Ray.y + thisObj->Ray.z* thisObj->Ray.z;
		float B = thisObj->Ray.x * px + thisObj->Ray.y * py + thisObj->Ray.z * pz;
		float C = px * px + py * py + pz * pz - p->Radius * p->Radius;

		if (A == 0.0f)
			continue; // レイの長さが0

		float s = B * B - A * C;
		if (s < 0.0f)
			continue; // 衝突していない

		s = sqrtf(s);
		float a1 = (B - s) / A;
		float a2 = (B + s) / A;

		if (a1 < 0.0f || a2 < 0.0f)
			continue; // レイの反対で衝突

		D3DXVECTOR3 _result;

		_result.x = thisObj->m_Pos.x + a1 * thisObj->Ray.x;
		_result.y = thisObj->m_Pos.y + a1 * thisObj->Ray.y;
		_result.z = thisObj->m_Pos.z + a1 * thisObj->Ray.z;

		thisObj->ResultPos = _result;

		_ReturnTargetObjList.push_back(p->ThisObj);
	}

	return _ReturnTargetObjList;
}

std::list<ObjBase*> CCollisionMgr::Raycast(ColBox* thisObj)
{
	std::list<ObjBase*> _ReturnTargetObjList;
	

	for (auto& p : m_Collisionlist)
	{
		if (p == thisObj)
			continue;

		D3DXVECTOR3 vCross = D3DXVECTOR3(0, 0, 0);
		
		//m_ModelMesh = p->ThisObj->GetRender();

		if (thisObj->ModelMesh == NULL)
			continue;

		if (thisObj->ModelMesh->Intersect(thisObj->m_Pos, thisObj->Ray, true, &vCross))
		{
			_ReturnTargetObjList.push_back(p->ThisObj);
		}
	}

	return _ReturnTargetObjList;
}