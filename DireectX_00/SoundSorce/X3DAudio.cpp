#include"X3DAudio.h"


CListener::CListener()
{
	//m_listener = { 0 };
}

CListener::~CListener()
{
}



CEmitter::CEmitter()
{
	/*m_emitter = { 0 };

	m_emitter.ChannelCount = 1;
	m_emitter.CurveDistanceScaler = FLT_MIN;*/

}

CEmitter::~CEmitter()
{
}

void CEmitter::SetEmitter(D3DMATRIX* matrix)
{

	/*m_emitter = { 0 };

	m_emitter.ChannelCount = 1;
	m_emitter.CurveDistanceScaler = FLT_MIN;*/

	X3DAUDIO_EMITTER emitter;
	emitter = { 0 };

	emitter.ChannelCount = 1;
	emitter.CurveDistanceScaler = FLT_MIN;


	m_emitter.push_back(emitter);

}