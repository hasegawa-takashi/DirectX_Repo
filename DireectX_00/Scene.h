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
	void CSceneMgr::Init() {
		m_Run = true;
		// �V�[���̏���
	}

	//-------------------------------------------------------
	//
	//	�V�[���̐V�K�}��
	//
	//-------------------------------------------------------
	bool CSceneMgr::PushScene(CSceneBase* scene) {
		// ���݂̏������|�[�Y��
		if (!m_SceneVec.empty()) {
			m_SceneVec.back()->Pause();
		}

		// �V�[����z��̌��ɑ}��
		m_SceneVec.push_back(scene);
		m_SceneVec.back()->Init();

		return true;
	}

	//-------------------------------------------------------
	//
	//	�V�[���̍폜
	//
	//-------------------------------------------------------
	bool CSceneMgr::PopScene() {
		// �V�[�����Ȃ��ꍇ�I��
		if (m_SceneVec.empty()) {
			return false;
		}

		// �V�[���̍폜
		m_SceneVec.back()->Release();
		delete m_SceneVec.back();
		m_SceneVec.pop_back();

		return true;
	}

	//-------------------------------------------------------
	//
	//	�V�[���̌���
	//
	//-------------------------------------------------------
	bool CSceneMgr::ChangeScene(CSceneBase* scene) {
		// ���݂̃V�[�����Ȃ��ꍇ�I��
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
	//	�o�^�V�[���̍X�V
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
	//	�o�^�V�[���`��
	//
	//-------------------------------------------------------
	void CSceneMgr::Draw() {
		if (m_SceneVec.empty())
			return;

		HRESULT hr = GetDxMgr()->GetDxDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(128, 128, 255), 1.0f, 0);
		
		if (SUCCEEDED(GetDxMgr()->GetDxDevice()->BeginScene()))
		{
			// �ʏ�`��
			m_SceneVec.back()->Draw();
			// ���ߏ���
			GetRenderMgr()->RenderTransStart();
			// �ォ��̕`��
			m_SceneVec.back()->LateDraw();
			// UI���̍Ō�̕`��
			m_SceneVec.back()->UIDraw();
			// �`��̏I��
			GetRenderMgr()->RenderEnd();

		}

		CDebug::Instance()->Render();
		GetDxMgr()->GetDxDevice()->Present(NULL, NULL, NULL, NULL);
	}

	//-------------------------------------------------------
	//
	//	�V�[��mgr�̏I������
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



	//===== �����o�ϐ� =====
public:

private:
	std::list<CSceneBase*> m_SceneVec;
	CFade *fade;
protected:

};

//=============================================================================
// �f�o�C�X�Ăяo���p
//=============================================================================
inline CSceneMgr* GetSceneMgr()
{
	return CSceneMgr::Instance();
}
