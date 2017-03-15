#include "TrainingBot.h"

#define PATH_BillBord	_T("../data/Texture/Target.png")

TrainingBot::TrainingBot()
	:billnprd(nullptr)
{
}


TrainingBot::~TrainingBot()
{
	delete billnprd;
}

void TrainingBot::Init()
{
	delete billnprd;
	billnprd = nullptr;
	billnprd = new CBillbord();

	billnprd->CreateMake3DBillbord(PATH_BillBord, 1.5f, 1.5f, 0.0f, 1.0f, 0.0f, 1.0f);

	Collision.m_Pos.x = m_mtxWorld._41;
	Collision.m_Pos.y = m_mtxWorld._42;
	Collision.m_Pos.z = m_mtxWorld._43;

	Collision.Radius = 1.0f;

	CObjManager::Instance()->LateRenderPush(this);

}

void TrainingBot::Update()
{
	billnprd->Update(m_mtxWorld);
}

void TrainingBot::LateUpdate()
{

}

void TrainingBot::Draw()
{
	
}

void TrainingBot::LateDraw()
{
	billnprd->Render();
}

void TrainingBot::Release()
{

}

void TrainingBot::Pause()
{

}

bool TrainingBot::AllRelaseObj()
{
	return true;
}


CMeshRender* TrainingBot::GetRender()
{
	return m_ModelMesh;
}

void TrainingBot::SetidentNumb(int Numb)
{
	ObjNumb = Numb;
}

int TrainingBot::GetidentNumb()
{
	return ObjNumb;
}

void TrainingBot::SetPos(D3DXVECTOR3 Pos)
{
	m_Pos.x = m_mtxWorld._41 = Pos.x;
	m_Pos.y = m_mtxWorld._42 = Pos.y;
	m_Pos.z = m_mtxWorld._43 = Pos.z;
}
