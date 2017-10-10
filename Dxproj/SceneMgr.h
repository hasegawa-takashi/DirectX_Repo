#pragma once

class CSceneBase
{
public:
	CSceneBase() {}
	virtual ~CSceneBase() {}

	virtual void Init() {}
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual void Draw() {}
	virtual void LateDraw() {}
	virtual void UIDraw() {}
	virtual void Release() {}
	virtual void Pause() {}
protected:
	bool m_Initflag = false;
};

#include"includeheader.h"


class CSceneMgr : public CSingleton<CSceneMgr>
{
public:
	CSceneMgr();
	~CSceneMgr();
	
	bool CreateScene();

	bool DeleteScene();
	
	bool ChangeScene();

	void SceneMigration();

	void Init();

	void Update();

	void Draw();

	void Release();

	void Pause();

	template <typename T>
	void PushScene()
	{
		m_SceneCreaterFunclist.push_back([]()->CSceneBase* {return new T; });
	}

private:


	std::list<CSceneBase*(*)()> m_SceneCreaterFunclist;
	CSceneBase* m_CurrentScene = nullptr;
	bool m_SceneChangeApply;

};