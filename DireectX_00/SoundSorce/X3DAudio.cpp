#include"X3DAudio.h"


CListener::CListener()
{
	m_listener = { 0 };
}

CListener::~CListener()
{
}

void CListener::Update()
{
	m_listener.OrientFront;		//	�O����
	m_listener.OrientTop;		//	�����
	m_listener.pCone;			//	���o�͈� NULL���ƑS����
	m_listener.Position;		//	���W
	m_listener.Velocity;		//	�ړ���?�ړ��x�N�g���̑傫���H
}

void CListener::SetListener(D3DMATRIX* matrix)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////

CEmitter::CEmitter()
{

}

CEmitter::~CEmitter()
{
}

void CEmitter::SetEmitter(D3DMATRIX* matrix)
{

	m_Emitter = { 0 };

	m_Emitter.ChannelCount = 1;
	m_Emitter.CurveDistanceScaler = FLT_MIN;
	
	// �}�g���N�X�̓o�^
	m_Emitterlist.push_back(matrix);
}

void CEmitter::Update()
{

}