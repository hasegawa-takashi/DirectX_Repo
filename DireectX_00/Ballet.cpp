#include "Ballet.h"


CBallet::CBallet()
{
}


CBallet::~CBallet()
{
}

//----------------------------
// --- �I�u�W�F�N�g�̏�����
bool CBallet::GetHitCheck()
{
	if (!Hitflag)
		return false;

	Hitflag = false;
	ShotFlag = false;
	return true;

}

//----------------------------
// --- �I�u�W�F�N�g�̏�����
void CBallet::Init()
{
	//ReloadFlag = false;
	//Hitflag = false;
	//HitCnt = 0;
}

//----------------------------
// --- �I�u�W�F�N�g�̍X�V
void CBallet::Update()
{

	if (!ShotFlag )
		return;

	// �G�ɓ������Ă���
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
		
		// ���͂Ƃ�����I��

	}

	
	// �t�B�[���h�ɓ������Ă���
	if (CObjManager::Instance()->CollisonCheck(ID_FIELD, COL_RAY, Collision))
	{

	}

}

//----------------------------
// --- �I�u�W�F�N�g�̕`��
void CBallet::Draw()
{

}

//----------------------------
// --- �I�u�W�F�N�g�̍폜
void CBallet::Release()
{
	// ���͂Ƃ�����I��
	ShotFlag = false;
	//ReloadFlag = true;
}

//----------------------------------------
// --- �e�̐���
bool CBallet::CreateBallet(BulletBox bullet)
{
	// �t���O����
	if (ShotFlag == true)
		return false;

	ShotFlag = true;

	// �ϐ��̏�����
	m_Pos = bullet.Pos;
	m_Dir = bullet.Dir;
	m_Range = bullet.Length;
	m_MaxError = bullet.SwingRange;
	Collision.m_Pos = bullet.Pos;
	Collision.Ray = bullet.Dir;

	return true;

}