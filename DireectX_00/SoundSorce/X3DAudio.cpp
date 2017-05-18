#include"X3DAudio.h"


CListener::CListener()
{
	m_listener = { 0 };
}

CListener::~CListener()
{
}



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
	
	// ƒ}ƒgƒŠƒNƒX‚Ì“o˜^
	m_Emitterlist.push_back(matrix);
}

void CEmitter::Update()
{

}