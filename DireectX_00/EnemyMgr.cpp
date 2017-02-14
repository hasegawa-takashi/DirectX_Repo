#include "EnemyMgr.h"
#include "TrainingBot.h"


CEnemyMgr::CEnemyMgr()
{
	
}


CEnemyMgr::~CEnemyMgr()
{
}

void CEnemyMgr::Init()
{

	// ‚±‚ê‚Íbot‚¶‚á‚È‚¢
	InitPos[0] = D3DXVECTOR3(0, 0, 0);

	// ‚±‚±‚©‚çbot
	InitPos[1] = D3DXVECTOR3(-75, 7, 57);
	InitPos[2] = D3DXVECTOR3(-121, 0.0f, 55);
	InitPos[3] = D3DXVECTOR3(-36, 8, 87);
	//InitPos[4] = D3DXVECTOR3(29, 0.0f, 35);


	for (int loop = 0; loop < MAX_BOT; loop++)
	{
		CObjManager::Instance()->PushObj(new TrainingBot, ID_ENEMY);
	}

	CObjManager::Instance()->SerchObj(ID_ENEMY,EnemyMap);

	int loop = 0;

	for (auto itr = EnemyMap.begin(); itr != EnemyMap.end(); itr++, loop++)
	{
		if (itr == EnemyMap.end())
			break;

		itr->second->SetPos(InitPos[loop]);
	}
}

void CEnemyMgr::Update()
{

}

void CEnemyMgr::LateUpdate()
{

}

void CEnemyMgr::Draw()
{

}

void CEnemyMgr::LateDraw()
{

}

void CEnemyMgr::Release()
{
	int a = 0;
}

void CEnemyMgr::Pause()
{

}

bool CEnemyMgr::AllRelaseObj()
{
	return true;
}

ColBox CEnemyMgr::GetCol()
{
	return Collision;
}

CMeshRender* CEnemyMgr::GetRender()
{
	return m_ModelMesh;
}

void CEnemyMgr::SetidentNumb(int Numb)
{
	ObjNumb = Numb;
}

int CEnemyMgr::GetidentNumb()
{
	return ObjNumb;
}