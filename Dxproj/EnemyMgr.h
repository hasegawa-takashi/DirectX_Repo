#pragma once
#include "includeheader.h"
#include"Enemy.h"


class CEnemyMgr : public ObjBase
{
public:
	CEnemyMgr();
	~CEnemyMgr();

	void Init();
	void Update();

private:
	void CreateEnemyCall();

	int m_NowLiveCnt = 0; // 現在の敵の数
	int m_MAX_ENEMY;
	int m_SpwnTimeCnt = 0;		// 次の生成までの時間
	int m_Spwntimelimit;
	int m_GameTime;
	float m_EnemySpd = 0.5f;
	int m_SpwnEnemyTotal = 0;
};

