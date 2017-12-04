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
	if (!m_ObjListArray.empty())
	{
		for (auto& list : m_ObjListArray)
		{
			delete list;
		}
	}

	if (!m_HoldDeletelistpair.empty())
	{
		m_HoldDeletelistpair.clear();
	}

	m_Numb = 0;

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
	// �I�u�W�F�N�g�̓o�^ + �ԍ��̓o�^
	assert(ID < m_ObjListArray.size());
	m_ObjListArray[ID]->AddObject(obj);
	obj->SetidentNumb(m_Numb);
	obj->SetObjNameNumb(ID);
	m_Numb++;

	return true;
}

int CObjMgr::GetObjCnt(int id)
{
	return m_ObjListArray[id]->GetListCnt();
}

bool CObjMgr::PopObj(int ID, int Numb)
{
	m_HoldDeletelistpair.push_back(std::make_pair(ID, Numb) );
	return true;
}

std::list<ObjBase*> CObjMgr::SerchObj(UINT ID)
{
	assert(ID < m_ObjListArray.size());
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

	// all�폜
	m_HoldDeletelistpair.clear();
}

/// <summary>
/// ���e���̑S�폜
/// </summary>
void CObjMgr::ObjAllClear()
{
	if (!m_ObjListArray.empty())
	{
		for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
		{
			delete m_ObjListArray[loop];
		}
	}

	if (!m_HoldDeletelistpair.empty())
	{
		m_HoldDeletelistpair.clear();
	}
	
	for (auto& list : m_ObjListArray)
	{
		list = new ObjList();
	}

	m_Numb = 0;
}