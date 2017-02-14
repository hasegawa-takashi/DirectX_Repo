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
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Draw() = 0;
	virtual void LateDraw() = 0;
	virtual void UIDraw() = 0;
	virtual void Release() = 0;
	virtual void Pause() = 0;
};

//==========================================================
// CSceneMgr
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

		CFade::Instance()->SetFade();
		
		CFade::Instance()->FadeOut();

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
		/*for( auto itr = m_SceneVec.begin(); itr != m_SceneVec.end(); itr++ ) {
			( *itr )->Update();
			}*/

		if (CFade::Instance()->FadeIn())
		{
			m_SceneVec.back()->Update();

			m_SceneVec.back()->LateUpdate();
		}


	}

	//-------------------------------------------------------
	//
	//	�o�^�V�[���`��
	//
	//-------------------------------------------------------
	void CSceneMgr::Draw() {
		if (m_SceneVec.empty())
			return;


		HRESULT hr = CWindow::Instance()->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(128, 128, 255), 1.0f, 0);

		hr;

		if (SUCCEEDED(CWindow::Instance()->GetDevice()->BeginScene()))
		{

			// �ʏ�`��
			m_SceneVec.back()->Draw();

			// ���߂����
			CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			m_SceneVec.back()->LateDraw();

			m_SceneVec.back()->UIDraw();

			CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			CWindow::Instance()->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

			
			CWindow::Instance()->GetDevice()->EndScene();
		}

		CFade::Instance()->DrawFade();

		CDebug::Instance()->Render();

		CWindow::Instance()->GetDevice()->Present(NULL, NULL, NULL, NULL);
		
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
