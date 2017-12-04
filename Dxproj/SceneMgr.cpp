#include "SceneMgr.h"



CSceneMgr::CSceneMgr()
{
}


CSceneMgr::~CSceneMgr()
{
	Complete_type_safe_delete(m_CurrentScene);
	m_SceneCreaterFunclist.clear();
}

bool CSceneMgr::CreateScene()
{
	auto _CreateFunc = m_SceneCreaterFunclist.back();
	m_SceneCreaterFunclist.pop_back();
	m_CurrentScene = _CreateFunc();

	return true;
}

bool CSceneMgr::DeleteScene()
{
	if (m_CurrentScene == nullptr)
		return true;

	Complete_type_safe_delete(m_CurrentScene);
	
	return true;
}

bool CSceneMgr::ChangeScene()
{
	m_SceneChangeApply = true;

	return true;
}

void CSceneMgr::SceneMigration()
{
	if (m_SceneChangeApply)
	{
		if (m_SceneCreaterFunclist.empty())
			return;

		std::list<std::list<ObjBase*>> ExcludeObjList = CObjMgr::Getintance().ExculdeObj();
		

		if (!DeleteScene())
			return;

		// �e�V�[���̂��|��
		CObjMgr::Getintance().ObjAllClear();
		CCollisionMgr::Getintance().ResetCollisionList();

		if (!CreateScene())
			return;

		for (auto& _Obj : ExcludeObjList )
		{
			for (auto& _pentityObj : _Obj)
			{
				CObjMgr::Getintance().PushObj(_pentityObj, _pentityObj->GetObjName());
			}
		}
		m_SceneChangeApply = false;
	}
}

void CSceneMgr::Init()
{
	if (m_CurrentScene == nullptr) 
		return;
	// �V�[���̏���
	m_CurrentScene->Init();
}

void CSceneMgr::Update()
{
	if (m_CurrentScene == nullptr)
		return;
	// �V�[���̏���
	m_CurrentScene->Update();
	m_CurrentScene->LateUpdate();

	CCamera::Getintance().LateUpdate();
}

void CSceneMgr::Draw()
{
	if (m_CurrentScene == nullptr)
		return;
	// �V�[���̏���
	
	if (CRenderFormat::Getintance().StartRender())
	{

		m_CurrentScene->Draw();

		CRenderFormat::Getintance().TransmissionDraw();
		m_CurrentScene->LateDraw();
		CCamera::Getintance().LateDraw();
		CDebug::Getintance().Render();
		m_CurrentScene->UIDraw();
	
	}

	CRenderFormat::Getintance().EndRender();

}

void CSceneMgr::Release()
{
	if (m_CurrentScene == nullptr)
		return;
	m_CurrentScene->Release();
	CCamera::Getintance().Release();
}

void CSceneMgr::Pause()
{
	if (m_CurrentScene == nullptr)
		return;
	m_CurrentScene->Pause();
}