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
	m_listener.OrientFront;		//	前方向
	m_listener.OrientTop;		//	上方向
	m_listener.pCone = NULL;	//	聴覚範囲 NULLだと全方向
	m_listener.Position;		//	座標
	m_listener.Velocity;		//	移動量?移動ベクトルの大きさ？
}

void CListener::SetListener(D3DXMATRIX* matrix)
{
	m_listenerMtx = matrix;


	D3DXVECTOR3 Pos;
	D3DXVECTOR3 forvec;
	D3DXVECTOR3 upvec;

	CCalculation::CalcLookAtMatrix(matrix, &Pos,&forvec,&upvec);

	m_listener.OrientFront = forvec;
	m_listener.OrientTop   = upvec;
	m_listener.pCone = NULL;
	m_listener.Position = Pos;
	m_listener.Velocity = D3DXVECTOR3(0,0,0);

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
	
	// マトリクスの登録
	m_Emitterlist.push_back(matrix);
}

void CEmitter::Update()
{

}