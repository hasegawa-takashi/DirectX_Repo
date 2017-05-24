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
	
	// マトリクスの登録
	m_EmitterMatrix = matrix;
	

}

void CEmitter::Update()
{

	D3DXVECTOR3 Pos;
	D3DXVECTOR3 forvec;
	D3DXVECTOR3 upvec;

	CCalculation::CalcLookAtMatrix(m_EmitterMatrix, &Pos, &forvec, &upvec);

	m_Emitter.OrientFront = forvec;
	m_Emitter.OrientTop = upvec;
	m_Emitter.Position = Pos;
	m_Emitter.Velocity = D3DXVECTOR3(0, 0, 0);

}


//////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//
//	リスナーの設定
//
bool C3DSound::SetListener(D3DXMATRIX** matrix)
{
	// もうあるよ
	if (m_VoiceListener != NULL)
		return false;

	m_VoiceListener->SetListener(*matrix);

	return true;

}

C3DSound::C3DSound()
{

	m_VoiceListener = new CListener();

	// 3DSoundの初期化
	X3DAudioInitialize(SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | SPEAKER_FRONT_CENTER |
		SPEAKER_LOW_FREQUENCY | SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT, X3DAUDIO_SPEED_OF_SOUND, m_X3DInstance);

	// DSPSetteingの設定
	m_X3DDsp = { 0 };
	FLOAT32* matrix = new FLOAT32[6];
	m_X3DDsp.SrcChannelCount = 1;
	m_X3DDsp.DstChannelCount = 6;
	m_X3DDsp.pMatrixCoefficients = matrix;
	delete matrix;
}

C3DSound::~C3DSound()
{

	delete m_VoiceListener;
}

X3DAUDIO_DSP_SETTINGS C3DSound::Calc3DAudio(D3DXMATRIX* emitter)
{



	//X3DAudioCalculate(m_X3DInstance,&m_VoiceListener,&emitter,);

	return m_X3DDsp;

}