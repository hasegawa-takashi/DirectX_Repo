
// --- インクルード
#include "ObjManager.h"
#include"Debug.h"
#include<math.h>
#include <queue>
#include <string>
#include <functional>

//-------------------------------------------------------
//
//	Objectのデストラクタ
//
//-------------------------------------------------------
CObjManager::~CObjManager()
{
	AllRelaseObj();
}

//-------------------------------------------------------
//
//	Objectの初期化
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
//	Objectの更新
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
//	Objectの更新
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
//	Objectの描画
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
//	Objectの描画
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

	// ここでソートをかける
	//std::sort(TranslucentObj.begin(), TranslucentObj.end(), std::greater<std::pair<float, ObjBase*>>());

	// 半透明オブジェクトの描画
	for (auto itr = TranslucentObj.begin(); itr != TranslucentObj.end(); itr++)
	{
		
		itr->second->LateDraw();

		if (TranslucentObj.empty())
			return;
	}

}



//-------------------------------------------------------
//
//	Objectの描画
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
//	Objectのリリース
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

	// 多分これは必要ないと思う
	//CObjManager::Instance()->AllRelaseObj();
}

//-------------------------------------------------------
//
//	Objectの捜索
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
//	Objectの挿入
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

	// === 同じIDのmapに増やす場合 === //
	for (auto itr = ObjList.begin(); itr != ObjList.end(); itr++)
	{
		auto mapitr = itr->rbegin();
		if (mapitr->first == ID)
		{
			itr->insert(std::make_pair(ID, obj));
			mapitr->second->SetidentNumb(Numb);
			// 登録済みのIDと同じIDがあった場合ここで終了する
			return true;
		}
	}


	// === listに増やして挿入する場合 === //

	// 変数の初期化
	OBJMGR hoge = { std::make_pair(ID, obj) };
	// 代入
	ObjList.push_back(hoge);
	
	//	配列の一番後ろのobjに番号の割り振り
	auto itr = ObjList.back();
	auto mapitr = itr.rbegin();
	mapitr->second->SetidentNumb(Numb);
	flag = true;
	return flag;
}

//-------------------------------------------------------
//
//	Objectの削除
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
//	Objectの交換
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
//	Objectの全削除
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
			// --- EnemyMgrをデリート時にエラー
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
//	Objectを命名するためのクラス
//  ちょっと面倒でポインタの位置を名前として使用
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
// コリジョン判定呼び出し用の関数
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
			// 検索
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
// 球体判定
//=============================================================================
bool CObjManager::CollisionBSphere(ColBox &obb1, ColBox &obb2)
{

	if ((powf((obb1.m_Pos.x - obb2.m_Pos.x), 2) + powf(obb1.m_Pos.y - obb1.m_Pos.y, 2) + powf((obb1.m_Pos.z - obb1.m_Pos.z), 2) <= powf((obb1.Radius + obb2.Radius),2)))
		return true;

	return false;
}

//=============================================================================
// AABB判定
//=============================================================================
bool CObjManager::CollisionAABB(ObjBase* pObj, UINT ID)
{
	return false;
}

//=============================================================================
// OBB判定
//=============================================================================
bool CObjManager::CollisionOBB(ColBox &obb1, ColBox &obb2)
{
	// 各方向ベクトルの確保
	// （N***:標準化方向ベクトル）
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

	// 分離軸 : Ae1
	FLOAT rA = D3DXVec3Length(&Ae1);
	FLOAT rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	FLOAT L = fabs(D3DXVec3Dot(&Interval, &NAe1));
	if (L > rA + rB)
		return false; // 衝突していない

	// 分離軸 : Ae2
	rA = D3DXVec3Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe2));
	if (L > rA + rB)
		return false;

	// 分離軸 : Ae3
	rA = D3DXVec3Length(&Ae3);
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe3));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be1);
	L = fabs(D3DXVec3Dot(&Interval, &NBe1));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be2);
	L = fabs(D3DXVec3Dot(&Interval, &NBe2));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NBe3));
	if (L > rA + rB)
		return false;

	// 分離軸 : C11
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &NAe1, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C12
	D3DXVec3Cross(&Cross, &NAe1, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C13
	D3DXVec3Cross(&Cross, &NAe1, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C21
	D3DXVec3Cross(&Cross, &NAe2, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C22
	D3DXVec3Cross(&Cross, &NAe2, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C23
	D3DXVec3Cross(&Cross, &NAe2, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C31
	D3DXVec3Cross(&Cross, &NAe3, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C32
	D3DXVec3Cross(&Cross, &NAe3, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C33
	D3DXVec3Cross(&Cross, &NAe3, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離平面が存在しないので「衝突している」
	return true;
}

float CObjManager::LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3)
{
	// 3つの内積の絶対値の和で投影線分長を計算
	// 分離軸Sepは標準化されていること
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
		return false; // レイの長さが0

	float s = B * B - A * C;
	if (s < 0.0f)
		return false; // 衝突していない

	s = sqrtf(s);
	float a1 = (B - s) / A;
	float a2 = (B + s) / A;

	if (a1 < 0.0f || a2 < 0.0f)
		return false; // レイの反対で衝突

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
//	半透明オブジェクトの登録
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
//	View行列からカメラポジション
//
//-------------------------------------------------------
float CObjManager::CameraDistance(D3DXVECTOR3 SetPos)
{
	D3DXMATRIX ViewPos;
	GetDxMgr()->GetDxDevice()->GetTransform(D3DTS_VIEW, &ViewPos);
	D3DXMATRIX hoge = ViewPos;
	D3DXMatrixInverse(&hoge, NULL, &hoge);

	// カメラの現在のポジションの取得
	D3DXVECTOR3 vp{ hoge._41, hoge._42, hoge._43 };

	D3DXVECTOR3 VecDir = SetPos - vp;

	float result = D3DXVec3Length(&VecDir);

	return result;

}