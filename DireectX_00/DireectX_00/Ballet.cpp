#include "Ballet.h"


CBallet::CBallet()
{
}


CBallet::~CBallet()
{
}

//----------------------------
// --- オブジェクトの初期化
bool CBallet::GetHitCheck()
{
	if (!Hitflag)
		return false;

	Hitflag = false;
	ShotFlag = false;
	return true;

}

//----------------------------
// --- オブジェクトの初期化
void CBallet::Init()
{
	//ReloadFlag = false;
	//Hitflag = false;
	//HitCnt = 0;
}

//----------------------------
// --- オブジェクトの更新
void CBallet::Update()
{

	if (!ShotFlag )
		return;

	// 敵に当たってたら
	if (CObjManager::Instance()->CollisonCheck(ID_ENEMY, COL_RAY_SPHERE, Collision))
	{
		D3DXVECTOR3 in = m_Pos - Collision.ResultPos;
		FLOAT out = D3DXVec3Length(&in);

		if (out < m_Range)
		{
			if (CObjManager::Instance()->PopObj(Collision.m_SetObjId, Collision.IdentNumb))
			{
				Release();
				Hitflag = true;
				return;
			}
		}
		
		// 何はともあれ終了

	}

	
	// フィールドに当たってたら
	if (CObjManager::Instance()->CollisonCheck(ID_FIELD, COL_RAY, Collision))
	{

	}

}

//----------------------------
// --- オブジェクトの描画
void CBallet::Draw()
{

}

//----------------------------
// --- オブジェクトの削除
void CBallet::Release()
{
	// 何はともあれ終了
	ShotFlag = false;
	//ReloadFlag = true;
}

//----------------------------------------
// --- 弾の生成
bool CBallet::CreateBallet(BulletBox bullet)
{
	// フラグ立て
	if (ShotFlag == true)
		return false;

	ShotFlag = true;

	// 変数の初期化
	m_Pos = bullet.Pos;
	m_Dir = bullet.Dir;
	m_Range = bullet.Length;
	m_MaxError = bullet.SwingRange;
	Collision.m_Pos = bullet.Pos;
	Collision.Ray = bullet.Dir;

	return true;

}