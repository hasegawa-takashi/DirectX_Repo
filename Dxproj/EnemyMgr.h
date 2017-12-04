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

	int m_NowLiveCnt = 0; // Œ»İ‚Ì“G‚Ì”
	int m_MAX_ENEMY;
	int m_SpwnTimeCnt = 0;		// Ÿ‚Ì¶¬‚Ü‚Å‚ÌŠÔ
	int m_Spwntimelimit;
	int m_GameTime;
	float m_EnemySpd = 0.5f;
	int m_SpwnEnemyTotal = 0;
};

