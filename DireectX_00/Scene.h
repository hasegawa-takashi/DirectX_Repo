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
	void Init() {
		m_Run = true;
		if (m_pCurrentScene == nullptr) return;

		// シーンの準備
		m_pCurrentScene->Init();
	}

	//-------------------------------------------------------
	//
	//	シーンの新規挿入 TODO プライベートへ隠ぺい予定
	//
	//-------------------------------------------------------
	bool CreateScene();

	//-------------------------------------------------------
	//
	//	シーンの削除	TODO プライベートへ隠ぺい予定
	//
	//-------------------------------------------------------
	bool DeleteScene();

	//-------------------------------------------------------
	//
	//	シーンの交換
	//
	//-------------------------------------------------------
	bool ChangeScene();

	//-------------------------------------------------------
	//
	//	登録シーンの更新
	//
	//-------------------------------------------------------
	void CSceneMgr::Update();

	//-------------------------------------------------------
	//
	//	登録シーン描画
	//
	//-------------------------------------------------------
	void CSceneMgr::Draw();

	//-------------------------------------------------------
	//
	//	シーンmgrの終了処理
	//
	//-------------------------------------------------------
	void CSceneMgr::Release();
	
	//-------------------------------------------------------
	//
	//	次のSceneを設定
	//
	//-------------------------------------------------------
	template <typename T>
	void PushScene()
	{
		m_SceneCreatorFunctionList.push_back([]()->CSceneBase* {return new T; });
	}

	//-------------------------------------------------------
	//
	//	Sceneの移行用
	//
	//-------------------------------------------------------
	void Scenemigration();

private:

	

protected:
	bool m_Run;
	//===== メンバ変数 =====
public:

private:
	std::list<CSceneBase*(*)()> m_SceneCreatorFunctionList; // 待機シーン生成関数リスト
	CSceneBase* m_pCurrentScene = nullptr;				// 次に入れるScene

	bool SceneChangeApply = false;	// sceneの削除申請

protected:

};

//=============================================================================
// デバイス呼び出し用
//=============================================================================
inline CSceneMgr* GetSceneMgr()
{
	return CSceneMgr::Instance();
}
