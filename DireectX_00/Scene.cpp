#include "Scene.h"

//-------------------------------------------------------
//
//	シーンの新規挿入
//
//-------------------------------------------------------
bool CSceneMgr::CreateScene() {
	auto pCreateFunc = m_SceneCreatorFunctionList.back();
	m_SceneCreatorFunctionList.pop_back();
	m_pCurrentScene = pCreateFunc();
	return true;
}

//-------------------------------------------------------
//
//	シーンの削除
//
//-------------------------------------------------------
bool CSceneMgr::DeleteScene() {
	GetObjMgr()->Release();
	SAFE_DELETE(m_pCurrentScene);
	return true;
}

//-------------------------------------------------------
//
//	シーンの交換
//
//-------------------------------------------------------
bool CSceneMgr::ChangeScene(bool deleteExcludeObj) {
	// 次のシーンが設定されていない
	if (m_SceneCreatorFunctionList.empty())
		return false;

	// シーンをまたいで保持したいオブジェクトの取得
	// 遷移のタイミングで削除するため
	// ToDo削除回避
	if (deleteExcludeObj == true)
	{
		std::list<std::list<ObjBase*>> ExcludeObjList = GetObjMgr()->ExculdeObj();
		// シーンの削除
		if (!DeleteScene()) return false;

		// シーンの挿入
		if (!CreateScene()) return false;

		// シーンの初期化
		for (auto& pObj : ExcludeObjList)
		{
			for (auto& pentityObj : pObj)
			{
				GetObjMgr()->PushObj(pentityObj, pentityObj->GetIDNumb());
			}
		
		}
	}
	else
	{
		// シーンの削除
		if (!DeleteScene()) return false;

		// シーンの挿入
		if (!CreateScene()) return false;
	}

	m_pCurrentScene->Init();

	return true;
}

//-------------------------------------------------------
//
//	登録シーンの更新
//
//-------------------------------------------------------
void CSceneMgr::Update() {
	if (m_pCurrentScene == nullptr) return;
	m_pCurrentScene->Update();
	m_pCurrentScene->LateUpdate();
}

//-------------------------------------------------------
//
//	登録シーン描画
//
//-------------------------------------------------------
void CSceneMgr::Draw() {
	if (m_pCurrentScene == nullptr) return;
	HRESULT hr = GetDxMgr()->GetDxDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(128, 128, 255), 1.0f, 0);

	if (SUCCEEDED(GetDxMgr()->GetDxDevice()->BeginScene()))
	{
		// 通常描画
		m_pCurrentScene->Draw();
		// 透過処理
		GetRenderMgr()->RenderTransStart();
		// 後からの描画
		m_pCurrentScene->LateDraw();
		// UI等の最後の描画
		m_pCurrentScene->UIDraw();
		// 描画の終了
		GetRenderMgr()->RenderEnd();

	}

	CDebug::Instance()->Render();
	GetDxMgr()->GetDxDevice()->Present(NULL, NULL, NULL, NULL);
}

//-------------------------------------------------------
//
//	シーンmgrの終了処理
//
//-------------------------------------------------------
void CSceneMgr::Release() {
	SAFE_DELETE(m_pCurrentScene);
}