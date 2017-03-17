#include "Scene.h"

//-------------------------------------------------------
//
//	�V�[���̐V�K�}��
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
//	�V�[���̍폜
//
//-------------------------------------------------------
bool CSceneMgr::DeleteScene() {
	GetObjMgr()->Release();
	SAFE_DELETE(m_pCurrentScene);
	return true;
}

//-------------------------------------------------------
//
//	�V�[���̌���
//
//-------------------------------------------------------
bool CSceneMgr::ChangeScene(bool deleteExcludeObj) {
	// ���̃V�[�����ݒ肳��Ă��Ȃ�
	if (m_SceneCreatorFunctionList.empty())
		return false;

	// �V�[�����܂����ŕێ��������I�u�W�F�N�g�̎擾
	// �J�ڂ̃^�C�~���O�ō폜���邽��
	// ToDo�폜���
	if (deleteExcludeObj == true)
	{
		std::list<std::list<ObjBase*>> ExcludeObjList = GetObjMgr()->ExculdeObj();
		// �V�[���̍폜
		if (!DeleteScene()) return false;

		// �V�[���̑}��
		if (!CreateScene()) return false;

		// �V�[���̏�����
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
		// �V�[���̍폜
		if (!DeleteScene()) return false;

		// �V�[���̑}��
		if (!CreateScene()) return false;
	}

	m_pCurrentScene->Init();

	return true;
}

//-------------------------------------------------------
//
//	�o�^�V�[���̍X�V
//
//-------------------------------------------------------
void CSceneMgr::Update() {
	if (m_pCurrentScene == nullptr) return;
	m_pCurrentScene->Update();
	m_pCurrentScene->LateUpdate();
}

//-------------------------------------------------------
//
//	�o�^�V�[���`��
//
//-------------------------------------------------------
void CSceneMgr::Draw() {
	if (m_pCurrentScene == nullptr) return;
	HRESULT hr = GetDxMgr()->GetDxDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(128, 128, 255), 1.0f, 0);

	if (SUCCEEDED(GetDxMgr()->GetDxDevice()->BeginScene()))
	{
		// �ʏ�`��
		m_pCurrentScene->Draw();
		// ���ߏ���
		GetRenderMgr()->RenderTransStart();
		// �ォ��̕`��
		m_pCurrentScene->LateDraw();
		// UI���̍Ō�̕`��
		m_pCurrentScene->UIDraw();
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
	SAFE_DELETE(m_pCurrentScene);
}