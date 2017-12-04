#include "EnemyMgr.h"



CEnemyMgr::CEnemyMgr()
{
	m_Spwntimelimit = 30;
	m_MAX_ENEMY = 5;
}


CEnemyMgr::~CEnemyMgr()
{
}

void CEnemyMgr::Init()
{
	m_Spwntimelimit = 30;
	m_MAX_ENEMY = 3;
	m_GameTime = 0;
	m_EnemySpd = 0.3f;
}

void CEnemyMgr::Update()
{

	int enemycnt = CObjMgr::Getintance().GetObjCnt(ID_ENEMY);

	m_GameTime++;
	m_SpwnTimeCnt++;
	CreateEnemyCall();

	if ((m_GameTime % 60) == 0)
	{
		if (m_EnemySpd > 5.0f)
		{
			m_EnemySpd += 0.04f;
		}

		if (enemycnt < 10)
		{
			m_MAX_ENEMY += 1;
		}
	}

	if (m_SpwnEnemyTotal % 1000 == 0)
	{
		m_MAX_ENEMY = 0;
	}
	else
	{
		m_MAX_ENEMY = 5;
	}

	m_NowLiveCnt = enemycnt;

}

void CEnemyMgr::CreateEnemyCall()
{
	if (m_SpwnTimeCnt >= m_Spwntimelimit)
	{
		if (m_NowLiveCnt < m_MAX_ENEMY)
		{
			CObjMgr::Getintance().PushObj(new CEnemy(m_EnemySpd),ID_ENEMY);
			m_NowLiveCnt++;
		}
		m_SpwnTimeCnt = 0;
		m_SpwnEnemyTotal++;
	}

}