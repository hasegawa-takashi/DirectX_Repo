#pragma once

#include<list>
#include"Window.h"
#include"Fade.h"
#include"FPS.h"
#include"Debug.h"

//==========================================================
// CSceneBass
//==========================================================
class CSceneBase {

public:
	CSceneBase(){}
	virtual ~CSceneBase(){}

	// 継承するメッセージ
	virtual void Init()			{}
	virtual void Update()		{}
	virtual void LateUpdate()	{}
	virtual void Draw()			{}
	virtual void LateDraw()		{}
	virtual void UIDraw()		{}
	virtual void Release()		{}
	virtual void Pause()		{}
};

//==========================================================
// CSceneMgr
//
// TODO　初期化のタイミングがおかしいためにリリースでエラーをはく
//
//==========================================================
class CSceneMgr {
	//===== メンバ関数 =====
public:
	~CSceneMgr(){
		Release();
	}

	static CSceneMgr* Instance(void) {
		static CSceneMgr _instance;
		return &_instance;
	}

	//-------------------------------------------------------
	//
	//	シーンmgrの初期化
	//
	//-------------------------------------------------------
	void CSceneMgr::Init() {
		m_Run = true;
		// シーンの準備
	}

	//-------------------------------------------------------
	//
	//	シーンの新規挿入
	//
	//-------------------------------------------------------
	bool CSceneMgr::PushScene(CSceneBase* scene) {
		// 現在の処理をポーズに
		if (!m_SceneVec.empty()) {
			m_SceneVec.back()->Pause();
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
	bool CSceneMgr::PopScene() {
		// シーンがない場合終了
		if (m_SceneVec.empty()) {
			return false;
		}

		// シーンの削除
		m_SceneVec.back()->Release();
		delete m_SceneVec.back();
		m_SceneVec.pop_back();

		return true;
	}

	//-------------------------------------------------------
	//
	//	シーンの交換
	//
	//-------------------------------------------------------
	bool CSceneMgr::ChangeScene(CSceneBase* scene) {
		// 現在のシーンがない場合終了
		if (m_SceneVec.empty()) {
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
	void CSceneMgr::Update() {
		if (m_SceneVec.empty())
			return;
		m_SceneVec.back()->Update();

		m_SceneVec.back()->LateUpdate();
		
	}

	//-------------------------------------------------------
	//
	//	登録シーン描画
	//
	//-------------------------------------------------------
	void CSceneMgr::Draw() {
		if (m_SceneVec.empty())
			return;

		HRESULT hr = GetDxMgr()->GetDxDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(128, 128, 255), 1.0f, 0);
		
		if (SUCCEEDED(GetDxMgr()->GetDxDevice()->BeginScene()))
		{
			// 通常描画
			m_SceneVec.back()->Draw();
			// 透過処理
			GetRenderMgr()->RenderTransStart();
			// 後からの描画
			m_SceneVec.back()->LateDraw();
			// UI等の最後の描画
			m_SceneVec.back()->UIDraw();
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
		for (auto& p : m_SceneVec) {
			delete p;
		}
		m_SceneVec.clear();
		delete fade;
	}
		

private:

	

protected:
	bool m_Run;



	//===== メンバ変数 =====
public:

private:
	std::list<CSceneBase*> m_SceneVec;
	CFade *fade;
protected:

};

//=============================================================================
// デバイス呼び出し用
//=============================================================================
inline CSceneMgr* GetSceneMgr()
{
	return CSceneMgr::Instance();
}
