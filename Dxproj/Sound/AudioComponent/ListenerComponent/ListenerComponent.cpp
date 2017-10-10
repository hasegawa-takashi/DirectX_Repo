#include "ListenerComponent.h"

//-----------------------------------------------------------------
//
//	CListenerComponent
//		����+�������ݒ�
//
CListenerComponent::CListenerComponent()
{
}

CListenerComponent::~CListenerComponent()
{
}

void CListenerComponent::Init(D3DXMATRIX* matrix)
{
	m_listener = { 0 };
	m_listener.pCone = NULL;
	SetListener(matrix);
}

//-----------------------------------------------------------------
//
//	ComponentUpdate
//		���X�i�[�̍��W�X�V
//
void CListenerComponent::ComponentUpdate()
{
	GetX3DSoundMgr()->SetListener(m_listenerMtx);
}

//-----------------------------------------------------------------
//
//	SetListener
//		���X�i�[�̍��W,�ʒu�Ȃǂ̍X�V
//
void CListenerComponent::SetListener(D3DXMATRIX* matrix)
{
	m_listenerMtx = matrix;

	D3DXVECTOR3 Pos = { m_listenerMtx->_41,m_listenerMtx->_42,m_listenerMtx->_43 };
	D3DXVECTOR3 forvec = { m_listenerMtx->_31,m_listenerMtx->_32,m_listenerMtx->_33 };
	D3DXVECTOR3 upvec = { m_listenerMtx->_21,m_listenerMtx->_22,m_listenerMtx->_23 };
	
	m_listener.OrientFront	= forvec;
	m_listener.OrientTop	= upvec;
	m_listener.pCone = NULL;
	m_listener.Position = Pos;
	m_listener.Velocity = D3DXVECTOR3(0, 0, 0);

	m_Uselistener = true;

	GetX3DSoundMgr()->SetListener(matrix);

}