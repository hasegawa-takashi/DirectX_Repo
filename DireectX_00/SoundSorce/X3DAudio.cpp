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
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 forvec;
	D3DXVECTOR3 upvec;

	CCalculation::CalcLookAtMatrix(m_listenerMtx, &Pos, &forvec, &upvec);

	m_listener.OrientFront = forvec;
	m_listener.OrientTop = upvec;
	m_listener.pCone = NULL;
	m_listener.Position = Pos;
	m_listener.Velocity = D3DXVECTOR3(0, 0, 0);
}

void CListener::SetListener(D3DXMATRIX* matrix)
{
	m_listenerMtx = matrix;

	D3DXVECTOR3 Pos;
	D3DXVECTOR3 forvec;
	D3DXVECTOR3 upvec;

	CCalculation::CalcLookAtMatrix(m_listenerMtx, &Pos,&forvec,&upvec);

	m_listener.OrientFront = forvec;
	m_listener.OrientTop   = upvec;
	m_listener.pCone = NULL;
	m_listener.Position = Pos;
	m_listener.Velocity = D3DXVECTOR3(0,0,0);

	m_Uselistener = true;

}

//////////////////////////////////////////////////////////////////////////////////////////////

CEmitter::CEmitter()
{

}

CEmitter::~CEmitter()
{

}

void CEmitter::SetEmitter(D3DXMATRIX* matrix)
{

	m_Emitter = { 0 };

	m_Emitter.ChannelCount = 1;
	m_Emitter.CurveDistanceScaler = FLT_MIN;
	
	// ƒ}ƒgƒŠƒNƒX‚Ì“o˜^
	m_Emitterlist.push_back(matrix);
	

}

void CEmitter::Update()
{

	D3DXVECTOR3 Pos;
	D3DXVECTOR3 forvec;
	D3DXVECTOR3 upvec;

	for (auto itr = m_Emitterlist.begin(); itr != m_Emitterlist.end(); ++itr)
	{
		CCalculation::CalcLookAtMatrix(*itr, &Pos, &forvec, &upvec);

		m_Emitter.OrientFront = forvec;
		m_Emitter.OrientTop = upvec;
		m_Emitter.Position = Pos;
		m_Emitter.Velocity = D3DXVECTOR3(0, 0, 0);

	}
}