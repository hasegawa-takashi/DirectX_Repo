#include"CollisionBase.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCollisionBase::CCollisionBase()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCollisionBase::~CCollisionBase()
{
}


//=============================================================================
// ���̔���
//=============================================================================
list<ObjBase*> Sphere::ISCollision(ColBox &obb1, UINT ID)
{
	m_TargetObjList = GetObjMgr()->SerchObj(ID);

	for (auto& p : m_TargetObjList)
	{
		ColBox* colbox = p->GetCol();
		if ((powf(obb1.m_Pos.x - colbox->m_Pos.x, 2.0f) + powf(obb1.m_Pos.y - colbox->m_Pos.y, 2.0f) + powf((obb1.m_Pos.z - colbox->m_Pos.z), 2) <= powf((obb1.Radius + colbox->Radius), 2)))
		{

			m_ReturnTargetObjList.push_back(p);
		}
	}

	return m_ReturnTargetObjList;

}

//=============================================================================
// AABB����@TODO ������
//=============================================================================
list<ObjBase*> AABB::ISCollision(ColBox &obb1, UINT ID)
{
	return m_ReturnTargetObjList;
}

//=============================================================================
// OBB����
//=============================================================================
list<ObjBase*> OBB::ISCollision(ColBox &obb1, UINT ID)
{
	m_TargetObjList = GetObjMgr()->SerchObj(ID);

	for (auto& p : m_TargetObjList)
	{
		ColBox* colbox = p->GetCol();
		// �e�����x�N�g���̊m��
		// �iN***:�W���������x�N�g���j
		D3DXVECTOR3 Norma1_X;
		D3DXVECTOR3 Norma1_Y;
		D3DXVECTOR3 Norma1_Z;

		D3DXVECTOR3 Norma2_X;
		D3DXVECTOR3 Norma2_Y;
		D3DXVECTOR3 Norma2_Z;

		Norma1_X.x = obb1.WorldMtx._11;
		Norma1_X.y = obb1.WorldMtx._12;
		Norma1_X.z = obb1.WorldMtx._13;

		Norma1_Y.x = obb1.WorldMtx._21;
		Norma1_Y.y = obb1.WorldMtx._22;
		Norma1_Y.z = obb1.WorldMtx._23;

		Norma1_Z.x = obb1.WorldMtx._31;
		Norma1_Z.y = obb1.WorldMtx._32;
		Norma1_Z.z = obb1.WorldMtx._33;

		Norma2_X.x = colbox->WorldMtx._11;
		Norma2_X.y = colbox->WorldMtx._12;
		Norma2_X.z = colbox->WorldMtx._13;

		Norma2_Y.x = colbox->WorldMtx._21;
		Norma2_Y.y = colbox->WorldMtx._22;
		Norma2_Y.z = colbox->WorldMtx._23;

		Norma2_Z.x = colbox->WorldMtx._31;
		Norma2_Z.y = colbox->WorldMtx._32;
		Norma2_Z.z = colbox->WorldMtx._33;

		D3DXVECTOR3 NAe1 = Norma1_X, Ae1 = NAe1 * obb1.m_fLength[0];
		D3DXVECTOR3 NAe2 = Norma1_Y, Ae2 = NAe2 * obb1.m_fLength[1];
		D3DXVECTOR3 NAe3 = Norma1_Z, Ae3 = NAe3 * obb1.m_fLength[2];
		D3DXVECTOR3 NBe1 = Norma2_X, Be1 = NBe1 * colbox->m_fLength[0];
		D3DXVECTOR3 NBe2 = Norma2_Y, Be2 = NBe2 * colbox->m_fLength[1];
		D3DXVECTOR3 NBe3 = Norma2_Z, Be3 = NBe3 * colbox->m_fLength[2];
		D3DXVECTOR3 Interval = obb1.m_Pos - colbox->m_Pos;

		// ������ : Ae1
		FLOAT rA = D3DXVec3Length(&Ae1);
		FLOAT rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
		FLOAT L = fabs(D3DXVec3Dot(&Interval, &NAe1));
		if (L > rA + rB)
			continue; // �Փ˂��Ă��Ȃ�

					  // ������ : Ae2
		rA = D3DXVec3Length(&Ae2);
		rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &NAe2));
		if (L > rA + rB)
			continue;

		// ������ : Ae3
		rA = D3DXVec3Length(&Ae3);
		rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &NAe3));
		if (L > rA + rB)
			continue;

		// ������ : Be1
		rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
		rB = D3DXVec3Length(&Be1);
		L = fabs(D3DXVec3Dot(&Interval, &NBe1));
		if (L > rA + rB)
			continue;

		// ������ : Be2
		rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
		rB = D3DXVec3Length(&Be2);
		L = fabs(D3DXVec3Dot(&Interval, &NBe2));
		if (L > rA + rB)
			continue;

		// ������ : Be3
		rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
		rB = D3DXVec3Length(&Be3);
		L = fabs(D3DXVec3Dot(&Interval, &NBe3));
		if (L > rA + rB)
			continue;

		// ������ : C11
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &NAe1, &NBe1);
		rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// ������ : C12
		D3DXVec3Cross(&Cross, &NAe1, &NBe2);
		rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// ������ : C13
		D3DXVec3Cross(&Cross, &NAe1, &NBe3);
		rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// ������ : C21
		D3DXVec3Cross(&Cross, &NAe2, &NBe1);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// ������ : C22
		D3DXVec3Cross(&Cross, &NAe2, &NBe2);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// ������ : C23
		D3DXVec3Cross(&Cross, &NAe2, &NBe3);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// ������ : C31
		D3DXVec3Cross(&Cross, &NAe3, &NBe1);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
		rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// ������ : C32
		D3DXVec3Cross(&Cross, &NAe3, &NBe2);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// ������ : C33
		D3DXVec3Cross(&Cross, &NAe3, &NBe3);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
		L = fabs(D3DXVec3Dot(&Interval, &Cross));
		if (L > rA + rB)
			continue;

		// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
		_ReturnTargetObjList.push_back(p);

	}

	return m_ReturnTargetObjList;

}

//=============================================================================
// OBB�̌v�Z�Ɏg��
//=============================================================================
float OBB::LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	float r1 = fabs(D3DXVec3Dot(Sep, e1));
	float r2 = fabs(D3DXVec3Dot(Sep, e2));
	float r3 = e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0;
	return r1 + r2 + r3;
}

//=============================================================================
// Ray�Ƌ��̂̔���
//=============================================================================
list<ObjBase*> RaySphere::ISCollision(ColBox &obb1, UINT ID)
{
	m_TargetObjList = GetObjMgr()->SerchObj(ID);

	for (auto& p : m_TargetObjList)
	{

		ColBox* colbox = p->GetCol();
		float px = colbox->m_Pos.x - obb1.m_Pos.x;
		float py = colbox->m_Pos.y - obb1.m_Pos.y;
		float pz = colbox->m_Pos.z - obb1.m_Pos.z;

		float A = obb1.Ray.x * obb1.Ray.x + obb1.Ray.y * obb1.Ray.y + obb1.Ray.z* obb1.Ray.z;
		float B = obb1.Ray.x * px + obb1.Ray.y * py + obb1.Ray.z * pz;
		float C = px * px + py * py + pz * pz - colbox->Radius * colbox->Radius;

		if (A == 0.0f)
			continue; // ���C�̒�����0

		float s = B * B - A * C;
		if (s < 0.0f)
			continue; // �Փ˂��Ă��Ȃ�

		s = sqrtf(s);
		float a1 = (B - s) / A;
		float a2 = (B + s) / A;

		if (a1 < 0.0f || a2 < 0.0f)
			continue; // ���C�̔��΂ŏՓ�

		obb1.ResultPos.x = obb1.m_Pos.x + a1 * obb1.Ray.x;
		obb1.ResultPos.y = obb1.m_Pos.y + a1 * obb1.Ray.y;
		obb1.ResultPos.z = obb1.m_Pos.z + a1 * obb1.Ray.z;

		m_ReturnTargetObjList.push_back(p);
	}

	return m_ReturnTargetObjList;

}

//=============================================================================
// Ray�Ƌ��̂̔���
//=============================================================================
list<ObjBase*> Raycast::ISCollision(ColBox &obb1, UINT ID)
{
	m_TargetObjList = GetObjMgr()->SerchObj(ID);

	for (auto& p : m_TargetObjList)
	{
		D3DXVECTOR3 vCross = D3DXVECTOR3(0, 0, 0);
		m_ModelMesh = p->GetRender();

		if (m_ModelMesh == NULL)
			continue;

		if (m_ModelMesh->Intersect(obb1.m_Pos, obb1.Ray, true, &vCross))
		{
			m_ReturnTargetObjList.push_back(p);
		}
	}

	return m_ReturnTargetObjList;

}