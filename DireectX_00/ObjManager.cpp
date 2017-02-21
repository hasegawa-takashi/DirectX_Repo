
// --- �C���N���[�h
#include "ObjManager.h"
#include"Debug.h"
#include<math.h>
#include <queue>
#include <string>
#include <functional>

//-------------------------------------------------------
//
//	Object�̃f�X�g���N�^
//
//-------------------------------------------------------
CObjManager::~CObjManager()
{
	AllRelaseObj();
}

//-------------------------------------------------------
//
//	Object�̏�����
//
//-------------------------------------------------------
void CObjManager::Init()
{
	if (ObjList.empty())
		return;
		
	for (auto itr = ObjList.begin(); itr != ObjList.end(); itr++)
	{
		for (auto mapitr = itr->begin(); mapitr != itr->end(); mapitr++)
		{
			mapitr->second->Init();

			if (ObjList.empty())
				return;
		}
	}

}

//-------------------------------------------------------
//
//	Object�̍X�V
//
//-------------------------------------------------------
void CObjManager::Update()
{
	if (ObjList.empty())
		return;

	for (auto itr = ObjList.begin(); itr != ObjList.end() ; itr++)
	{
		for (auto mapitr = itr->begin() ; mapitr != itr->end() ; mapitr++)
		{
			mapitr->second->Update();

			if (ObjList.empty())
				return;

		}
	}
}

//-------------------------------------------------------
//
//	Object�̍X�V
//
//-------------------------------------------------------
void CObjManager::LateUpdate()
{
	if (ObjList.empty())
		return;

	for (auto itr = ObjList.begin(); itr != ObjList.end(); itr++)
	{
		for (auto mapitr = itr->begin(); mapitr != itr->end(); mapitr++)
		{
			mapitr->second->LateUpdate();
			
			if (ObjList.empty())
				return;
		}
	}
}

//-------------------------------------------------------
//
//	Object�̕`��
//
//-------------------------------------------------------
void CObjManager::Draw()
{

	if (ObjList.empty())
		return;

	for (auto itr = ObjList.begin(); itr != ObjList.end(); itr++)
	{
		for (auto mapitr = itr->begin(); mapitr != itr->end(); mapitr++)
		{
			mapitr->second->Draw();

			if (ObjList.empty())
				return;
		}
	}


}

//-------------------------------------------------------
//
//	Object�̕`��
//
//-------------------------------------------------------
void CObjManager::LateDraw()
{

	if (TranslucentObj.empty())
		return;

	/*for (auto itr = ObjList.begin(); itr != ObjList.end(); itr++)
	{
		for (auto mapitr = itr->begin(); mapitr != itr->end(); mapitr++)
		{
			mapitr->second->LateDraw();

			if (ObjList.empty())
				return;
		}
	}*/

	// �����Ń\�[�g��������
	//std::sort(TranslucentObj.begin(), TranslucentObj.end(), std::greater<std::pair<float, ObjBase*>>());

	// �������I�u�W�F�N�g�̕`��
	for (auto itr = TranslucentObj.begin(); itr != TranslucentObj.end(); itr++)
	{
		
		itr->second->LateDraw();

		if (TranslucentObj.empty())
			return;
	}

}



//-------------------------------------------------------
//
//	Object�̕`��
//
//-------------------------------------------------------
void CObjManager::UIDraw()
{
	if (ObjList.empty())
		return;

	for (auto itr = ObjList.begin(); itr != ObjList.end(); itr++)
	{
		for (auto mapitr = itr->begin(); mapitr != itr->end(); mapitr++)
		{
			mapitr->second->UIDraw();

			if (ObjList.empty())
				return;
		}
	}

}

//-------------------------------------------------------
//
//	Object�̃����[�X
//		
//-------------------------------------------------------
void CObjManager::Release()
{
	if (ObjList.empty())
		return;

	for (auto itr = ObjList.begin(); itr != ObjList.end(); itr++)
	{
		for (auto mapitr = itr->begin(); mapitr != itr->end(); mapitr++)
		{
			mapitr->second->Release();

			if (ObjList.empty())
				return;
		}
	}

	// ��������͕K�v�Ȃ��Ǝv��
	//CObjManager::Instance()->AllRelaseObj();
}

//-------------------------------------------------------
//
//	Object�̑{��
//
//-------------------------------------------------------
void CObjManager::SerchObj(UINT ID , OBJMGR& obj )
{
	if (ObjList.empty())
		return;

	for (auto itr = ObjList.begin(); itr != ObjList.end(); itr++)
	{
		for (auto mapitr = itr->begin(); mapitr != itr->end(); mapitr++)
		{
			if (mapitr->first == ID)
			{
				obj = *itr;
				return;
			}
		}
	}
}

//-------------------------------------------------------
//
//	Object�̑}��
//
//-------------------------------------------------------
bool CObjManager::PushObj( ObjBase* obj , UINT ID)
{
	bool flag = false;

	if (obj == NULL)
	{
		return false;
	}
	Numb++;

	// === ����ID��map�ɑ��₷�ꍇ === //
	for (auto itr = ObjList.begin(); itr != ObjList.end(); itr++)
	{
		auto mapitr = itr->rbegin();
		if (mapitr->first == ID)
		{
			itr->insert(std::make_pair(ID, obj));
			mapitr->second->SetidentNumb(Numb);
			// �o�^�ς݂�ID�Ɠ���ID���������ꍇ�����ŏI������
			return true;
		}
	}


	// === list�ɑ��₵�đ}������ꍇ === //

	// �ϐ��̏�����
	OBJMGR hoge = { std::make_pair(ID, obj) };
	// ���
	ObjList.push_back(hoge);
	
	//	�z��̈�Ԍ���obj�ɔԍ��̊���U��
	auto itr = ObjList.back();
	auto mapitr = itr.rbegin();
	mapitr->second->SetidentNumb(Numb);
	flag = true;
	return flag;
}

//-------------------------------------------------------
//
//	Object�̍폜
//
//-------------------------------------------------------
bool CObjManager::PopObj(int Type,int ID)
{
	if (ObjList.empty())
	{
		return false;
	}

	for (auto itr = ObjList.begin(); itr != ObjList.end(); itr++)
	{
		for (auto mapitr = itr->begin(); mapitr != itr->end(); mapitr++)
		{
			if (mapitr->first == Type)
			{
				if (mapitr->second->GetidentNumb() == ID)
				{
					
					itr->erase(mapitr);
					return true;
				}
			}
		}
	}

	return false;
}


//-------------------------------------------------------
//
//	Object�̌���
//
//-------------------------------------------------------
bool CObjManager::ChangeObj(int Numb, ObjBase* obj)
{
	if (ObjList.empty())
	{
		return false;
	}

	for (auto itr = ObjList.begin(); itr != ObjList.end(); itr++)
	{
		auto hoge = itr->find(Numb);

		if ( hoge != itr->end() )
		{
			return false;
		}
		else
		{
			OBJMGR maps;
			maps.insert(std::make_pair(Numb, obj));
			ObjList.insert(itr,maps);
		}
	}

	return true;

}

//-------------------------------------------------------
//
//	Object�̑S�폜
//
//-------------------------------------------------------
bool CObjManager::AllRelaseObj()
{
	if (ObjList.empty())
	{
		return false;
	}

	for (auto itr = ObjList.begin(); itr != ObjList.end(); itr++)
	{
		for (auto mapitr = itr->begin(); mapitr != itr->end(); mapitr++)
		{
			mapitr->second->Release();
			//-------------------------------------
			// --- EnemyMgr���f���[�g���ɃG���[
			delete mapitr->second;
			
			if ( ObjList.empty() )
				return true;
			
		}
	}

	ObjList.clear();
	
	return true;

}

//-------------------------------------------------------
//
//	Object�𖽖����邽�߂̃N���X
//  ������Ɩʓ|�Ń|�C���^�̈ʒu�𖼑O�Ƃ��Ďg�p
//
//-------------------------------------------------------
int CObjManager::RenameObj(UINT ID)
{
	if (ObjList.empty())
	{
		return -1;
	}

	int name = 0;

	switch (ID)
	{
	case ID_PLAYER:
		name = ID_PLAYER;
		break;

	case ID_ENEMY:
		name = ID_ENEMY;
		break;

	case ID_FIELD:
		name = ID_FIELD;
		break;

	case ID_BALLET:
		name = ID_BALLET;
		break;

	case ID_CAMERA:
		name = ID_CAMERA;
		break;

	case ID_OTHER:
		name = (int)&ObjList.back();
		break;

	default:
		break;
	}

	return name;

}

//=============================================================================
// �R���W��������Ăяo���p�̊֐�
//=============================================================================
bool CObjManager::CollisonCheck(UINT ID, int Colltype, ColBox &obb1)
{
	if (ObjList.empty())
	{
		return false;
	}


	for (auto& itr = ObjList.begin(); itr != ObjList.end(); itr++)
	{
		
		for (auto& mapitr = itr->begin(); mapitr != itr->end(); mapitr++)
		{


			D3DXVECTOR3 vCross = D3DXVECTOR3(0, 0, 0);
			// ����
			switch (Colltype)
			{
			case COL_SPHERE:
				if (CollisionBSphere(obb1, mapitr->second->GetCol()) && mapitr->first == ID)
				{
					ObjList.erase(itr);
					return true;
				}
				break;

			case COL_AABB:
				break;

			case COL_OBB:
				if (CollisionOBB(obb1, mapitr->second->GetCol()) && mapitr->first == ID)
				{
					ObjList.erase(itr);
					return true;
				}
				break;

			case COL_RAY:
				m_ModelMesh = mapitr->second->GetRender();

				if (m_ModelMesh == NULL)
					break;

				if (m_ModelMesh->Intersect(obb1.m_Pos, obb1.Ray, true, &vCross) && mapitr->first == ID)
				{
					obb1.ResultPos.x = vCross.x;
					obb1.ResultPos.y = vCross.y;
					obb1.ResultPos.z = vCross.z;
					obb1.m_SetObjId = mapitr->first;
					obb1.IdentNumb = mapitr->second->GetidentNumb();

					return true;
				}
				break;

			case COL_RAY_SPHERE:
				if (calcRaySphere(obb1, mapitr->second->GetCol()) && mapitr->first == ID)
				{
					obb1.m_SetObjId = mapitr->first;
					obb1.IdentNumb = mapitr->second->GetidentNumb();
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	return false;

}

//=============================================================================
// ���̔���
//=============================================================================
bool CObjManager::CollisionBSphere(ColBox &obb1, ColBox &obb2)
{

	if ((powf((obb1.m_Pos.x - obb2.m_Pos.x), 2) + powf(obb1.m_Pos.y - obb1.m_Pos.y, 2) + powf((obb1.m_Pos.z - obb1.m_Pos.z), 2) <= powf((obb1.Radius + obb2.Radius),2)))
		return true;

	return false;
}

//=============================================================================
// AABB����
//=============================================================================
bool CObjManager::CollisionAABB(ObjBase* pObj, UINT ID)
{
	return false;
}

//=============================================================================
// OBB����
//=============================================================================
bool CObjManager::CollisionOBB(ColBox &obb1, ColBox &obb2)
{
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

	Norma2_X.x = obb2.WorldMtx._11;
	Norma2_X.y = obb2.WorldMtx._12;
	Norma2_X.z = obb2.WorldMtx._13;

	Norma2_Y.x = obb2.WorldMtx._21;
	Norma2_Y.y = obb2.WorldMtx._22;
	Norma2_Y.z = obb2.WorldMtx._23;

	Norma2_Z.x = obb2.WorldMtx._31;
	Norma2_Z.y = obb2.WorldMtx._32;
	Norma2_Z.z = obb2.WorldMtx._33;

	D3DXVECTOR3 NAe1 = Norma1_X, Ae1 = NAe1 * obb1.m_fLength[0];
	D3DXVECTOR3 NAe2 = Norma1_Y, Ae2 = NAe2 * obb1.m_fLength[1];
	D3DXVECTOR3 NAe3 = Norma1_Z, Ae3 = NAe3 * obb1.m_fLength[2];
	D3DXVECTOR3 NBe1 = Norma2_X, Be1 = NBe1 * obb2.m_fLength[0];
	D3DXVECTOR3 NBe2 = Norma2_Y, Be2 = NBe2 * obb2.m_fLength[1];
	D3DXVECTOR3 NBe3 = Norma2_Z, Be3 = NBe3 * obb2.m_fLength[2];
	D3DXVECTOR3 Interval = obb1.m_Pos - obb2.m_Pos;

	// ������ : Ae1
	FLOAT rA = D3DXVec3Length(&Ae1);
	FLOAT rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	FLOAT L = fabs(D3DXVec3Dot(&Interval, &NAe1));
	if (L > rA + rB)
		return false; // �Փ˂��Ă��Ȃ�

	// ������ : Ae2
	rA = D3DXVec3Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe2));
	if (L > rA + rB)
		return false;

	// ������ : Ae3
	rA = D3DXVec3Length(&Ae3);
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe3));
	if (L > rA + rB)
		return false;

	// ������ : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be1);
	L = fabs(D3DXVec3Dot(&Interval, &NBe1));
	if (L > rA + rB)
		return false;

	// ������ : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be2);
	L = fabs(D3DXVec3Dot(&Interval, &NBe2));
	if (L > rA + rB)
		return false;

	// ������ : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NBe3));
	if (L > rA + rB)
		return false;

	// ������ : C11
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &NAe1, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C12
	D3DXVec3Cross(&Cross, &NAe1, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C13
	D3DXVec3Cross(&Cross, &NAe1, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C21
	D3DXVec3Cross(&Cross, &NAe2, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C22
	D3DXVec3Cross(&Cross, &NAe2, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C23
	D3DXVec3Cross(&Cross, &NAe2, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C31
	D3DXVec3Cross(&Cross, &NAe3, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C32
	D3DXVec3Cross(&Cross, &NAe3, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C33
	D3DXVec3Cross(&Cross, &NAe3, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
	return true;
}

float CObjManager::LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	float r1 = fabs(D3DXVec3Dot(Sep, e1));
	float r2 = fabs(D3DXVec3Dot(Sep, e2));
	float r3 = e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0;
	return r1 + r2 + r3;
}

bool CObjManager::calcRaySphere(ColBox &obb1, ColBox &obb2)
{
	float px = obb2.m_Pos.x - obb1.m_Pos.x;
	float py = obb2.m_Pos.y - obb1.m_Pos.y;
	float pz = obb2.m_Pos.z - obb1.m_Pos.z;

	float A = obb1.Ray.x * obb1.Ray.x + obb1.Ray.y * obb1.Ray.y + obb1.Ray.z* obb1.Ray.z;
	float B = obb1.Ray.x * px + obb1.Ray.y * py + obb1.Ray.z * pz;
	float C = px * px + py * py + pz * pz - obb2.Radius * obb2.Radius;

	if (A == 0.0f)
		return false; // ���C�̒�����0

	float s = B * B - A * C;
	if (s < 0.0f)
		return false; // �Փ˂��Ă��Ȃ�

	s = sqrtf(s);
	float a1 = (B - s) / A;
	float a2 = (B + s) / A;

	if (a1 < 0.0f || a2 < 0.0f)
		return false; // ���C�̔��΂ŏՓ�

	obb1.ResultPos.x = obb1.m_Pos.x + a1 * obb1.Ray.x;
	obb1.ResultPos.y = obb1.m_Pos.y + a1 * obb1.Ray.y;
	obb1.ResultPos.z = obb1.m_Pos.z + a1 * obb1.Ray.z;

	/*
	q2x = obb1.m_Pos.x + a2 * obb1.Ray.x;
	q2y = obb1.m_Pos.y + a2 * obb1.Ray.y;
	q2z = obb1.m_Pos.z + a2 * obb1.Ray.z;
	*/


	return true;
}

//-------------------------------------------------------
//
//	�������I�u�W�F�N�g�̓o�^
//
//-------------------------------------------------------
bool CObjManager::LateRenderPush( ObjBase* render)
{
	
	D3DXVECTOR3 PosA = render->GetPos();

	float ABLength = CameraDistance(PosA);

	TranslucentObj.push_back( std::make_pair(ABLength,render) );

	return true;
}

//-------------------------------------------------------
//
//	View�s�񂩂�J�����|�W�V����
//
//-------------------------------------------------------
float CObjManager::CameraDistance(D3DXVECTOR3 SetPos)
{
	D3DXMATRIX ViewPos;
	GetDxMgr()->GetDxDevice()->GetTransform(D3DTS_VIEW, &ViewPos);
	D3DXMATRIX hoge = ViewPos;
	D3DXMatrixInverse(&hoge, NULL, &hoge);

	// �J�����̌��݂̃|�W�V�����̎擾
	D3DXVECTOR3 vp{ hoge._41, hoge._42, hoge._43 };

	D3DXVECTOR3 VecDir = SetPos - vp;

	float result = D3DXVec3Length(&VecDir);

	return result;

}