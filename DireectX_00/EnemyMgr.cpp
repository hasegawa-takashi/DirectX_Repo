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

ColBox* CEnemyMgr::GetCol()
{
	return &Collision;
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