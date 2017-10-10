#include "ObjMgr.h"

CObjMgr::CObjMgr()
{
	for (auto& list : m_ObjListArray)
	{
		list = new ObjList();
	}
}

CObjMgr::~CObjMgr()
{
	Release();
	for (auto& list : m_ObjListArray)
	{
		delete list;
	}
}

void CObjMgr::Init()
{
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->Init();
	}
}

void CObjMgr::Update()
{
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->Update();
	}
}

void CObjMgr::LateUpdate()
{
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->LateUpdate();
	}
}

void CObjMgr::Draw()
{
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->Draw();
	}
}

void CObjMgr::LateDraw()
{
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->LateDraw();
	}
}

void CObjMgr::UIDraw()
{
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->UIDraw();
	}
}

void CObjMgr::Release()
{
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->Release();
	}
	m_Numb = 0;
}

void CObjMgr::Pause()
{
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->Pause();
	}
}

bool CObjMgr::PushObj(ObjBase* obj, UINT ID)
{
	// ÉIÉuÉWÉFÉNÉgÇÃìoò^ + î‘çÜÇÃìoò^
	m_ObjListArray[ID]->AddObject(obj);
	obj->SetidentNumb(m_Numb);
	m_Numb++;

	return true;
}

bool CObjMgr::PopObj(int ID, int Numb)
{
	m_HoldDeletelistpair.push_back(std::make_pair(ID, Numb) );
	return true;
}

std::list<ObjBase*> CObjMgr::SerchObj(UINT ID)
{
	return m_ObjListArray[ID]->GetObjList();
}

std::list<std::list<ObjBase*>>  CObjMgr::ExculdeObj()
{
	std::list<std::list<ObjBase*>> excludeObjlist;

	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		excludeObjlist.push_back(m_ObjListArray[loop]->GetExculdeObj());
	}

	return std::move(excludeObjlist);
}

void CObjMgr::ObjMigration()
{
	if (m_HoldDeletelistpair.empty())
		return;

	for (auto p = m_HoldDeletelistpair.begin(); p != m_HoldDeletelistpair.end(); p++)
	{
		m_ObjListArray[p->first]->RemoveObject(p->second);
	}

	// allçÌèú
	m_HoldDeletelistpair.clear();
}