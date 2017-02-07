#include "Scene.h"


CSceneMgr::CSceneMgr()
{
}


CSceneMgr::~CSceneMgr()
{
}

//-------------------------------------------------------
//
//	シーンmgrの初期化
//
//-------------------------------------------------------
void CSceneMgr::Init()
{

	m_Run = true;

}

//-------------------------------------------------------
//
//	シーンmgrの終了処理
//
//-------------------------------------------------------
void CSceneMgr::Release()
{

	delete [] &m_SceneVec;
}

//-------------------------------------------------------
//
//	シーンの新規挿入
//
//-------------------------------------------------------
bool CSceneMgr::PushScene(SceneBase* scene)
{
	// 現在の処理をポーズに
	if (!m_SceneVec.empty())
	{
		m_SceneVec.back()->Pause();;
	}

	// シーンを配列の後ろに挿入
	m_SceneVec.push_back(scene);
	m_SceneVec.back()->Init();

	return true;
}

//-------------------------------------------------------
//
//	シーンの削除
//
//-------------------------------------------------------
bool CSceneMgr::PopScene()
{
	// シーンがない場合終了
	if (!m_SceneVec.empty())
	{
		return false;
	}

	// シーンの削除
	m_SceneVec.back()->Release();
	m_SceneVec.pop_back();

	return true;
}

//-------------------------------------------------------
//
//	シーンの交換
//
//-------------------------------------------------------
bool CSceneMgr::ChangeScene(SceneBase* scene)
{
	// 現在のシーンがない場合終了
	if (!m_SceneVec.empty())
	{
		return false;
	}

	if (!PopScene())
		return false;
	
	if (!PushScene(scene))
		return false;

	return true;
}

//-------------------------------------------------------
//
//	登録シーンの更新
//
//-------------------------------------------------------
void CSceneMgr::Update()
{
	if (!m_SceneVec.empty())
		return;
	
	//m_SceneVec.back()->Update(this);

	for (auto itr = m_SceneVec.begin(); itr != m_SceneVec.end(); itr++)
	{
		(*itr)->Update(this);
	}

}

//-------------------------------------------------------
//
//	登録シーン描画
//
//-------------------------------------------------------
void CSceneMgr::Draw()
{
	if (!m_SceneVec.empty())
		return;
	
	//m_SceneVec.back()->Draw(this);

	for (auto itr = m_SceneVec.begin(); itr != m_SceneVec.end(); itr++)
	{
		(*itr)->Draw(this);
	}

}