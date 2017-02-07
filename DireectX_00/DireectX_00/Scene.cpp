#include "Scene.h"


CSceneMgr::CSceneMgr()
{
}


CSceneMgr::~CSceneMgr()
{
}

//-------------------------------------------------------
//
//	�V�[��mgr�̏�����
//
//-------------------------------------------------------
void CSceneMgr::Init()
{

	m_Run = true;

}

//-------------------------------------------------------
//
//	�V�[��mgr�̏I������
//
//-------------------------------------------------------
void CSceneMgr::Release()
{

	delete [] &m_SceneVec;
}

//-------------------------------------------------------
//
//	�V�[���̐V�K�}��
//
//-------------------------------------------------------
bool CSceneMgr::PushScene(SceneBase* scene)
{
	// ���݂̏������|�[�Y��
	if (!m_SceneVec.empty())
	{
		m_SceneVec.back()->Pause();;
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
bool CSceneMgr::PopScene()
{
	// �V�[�����Ȃ��ꍇ�I��
	if (!m_SceneVec.empty())
	{
		return false;
	}

	// �V�[���̍폜
	m_SceneVec.back()->Release();
	m_SceneVec.pop_back();

	return true;
}

//-------------------------------------------------------
//
//	�V�[���̌���
//
//-------------------------------------------------------
bool CSceneMgr::ChangeScene(SceneBase* scene)
{
	// ���݂̃V�[�����Ȃ��ꍇ�I��
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
//	�o�^�V�[���̍X�V
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
//	�o�^�V�[���`��
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