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

	// �p�����郁�b�Z�[�W
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
// TODO�@�������̃^�C�~���O�������������߂Ƀ����[�X�ŃG���[���͂�
//
//==========================================================
class CSceneMgr {
	//===== �����o�֐� =====
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
	//	�V�[��mgr�̏�����
	//
	//-------------------------------------------------------
	void Init() {
		m_Run = true;
		if (m_pCurrentScene == nullptr) return;

		// �V�[���̏���
		m_pCurrentScene->Init();
	}

	//-------------------------------------------------------
	//
	//	�V�[���̐V�K�}�� TODO �v���C�x�[�g�։B�؂��\��
	//
	//-------------------------------------------------------
	bool CreateScene();

	//-------------------------------------------------------
	//
	//	�V�[���̍폜	TODO �v���C�x�[�g�։B�؂��\��
	//
	//-------------------------------------------------------
	bool DeleteScene();

	//-------------------------------------------------------
	//
	//	�V�[���̌���
	//
	//-------------------------------------------------------
	bool ChangeScene();

	//-------------------------------------------------------
	//
	//	�o�^�V�[���̍X�V
	//
	//-------------------------------------------------------
	void CSceneMgr::Update();

	//-------------------------------------------------------
	//
	//	�o�^�V�[���`��
	//
	//-------------------------------------------------------
	void CSceneMgr::Draw();

	//-------------------------------------------------------
	//
	//	�V�[��mgr�̏I������
	//
	//-------------------------------------------------------
	void CSceneMgr::Release();
	
	//-------------------------------------------------------
	//
	//	����Scene��ݒ�
	//
	//-------------------------------------------------------
	template <typename T>
	void PushScene()
	{
		m_SceneCreatorFunctionList.push_back([]()->CSceneBase* {return new T; });
	}

	//-------------------------------------------------------
	//
	//	Scene�̈ڍs�p
	//
	//-------------------------------------------------------
	void Scenemigration();

private:

	

protected:
	bool m_Run;
	//===== �����o�ϐ� =====
public:

private:
	std::list<CSceneBase*(*)()> m_SceneCreatorFunctionList; // �ҋ@�V�[�������֐����X�g
	CSceneBase* m_pCurrentScene = nullptr;				// ���ɓ����Scene

	bool SceneChangeApply = false;	// scene�̍폜�\��

protected:

};

//=============================================================================
// �f�o�C�X�Ăяo���p
//=============================================================================
inline CSceneMgr* GetSceneMgr()
{
	return CSceneMgr::Instance();
}
