#include "EmitterComponent.h"


//-----------------------------------------------------------------
//
//	CEmitterComponent
//		生成+初期化設定
//
CEmitterComponent::CEmitterComponent()
{
	m_Emitter = { 0 };

	m_Emitter.pCone = NULL;
	/*m_Emitter.pCone->OuterVolume = 1.0f;
	m_Emitter.pCone->OuterLPF = 1.0f;
	m_Emitter.pCone->OuterReverb = 1.0f;*/

	m_Emitter.ChannelCount = 2;
	m_Emitter.CurveDistanceScaler = FLT_MIN;
	m_Emitter.pVolumeCurve = NULL;
	m_Emitter.pChannelAzimuths = emitterAzimuths;

	m_Emitter.pVolumeCurve = (X3DAUDIO_DISTANCE_CURVE*)&X3DAudioDefault_LinearCurve;
	m_Emitter.pLFECurve = (X3DAUDIO_DISTANCE_CURVE*)&Emitter_LFE_Curve;
	m_Emitter.pLPFDirectCurve = NULL; // use default curve
	m_Emitter.pLPFReverbCurve = NULL; // use default curve
	m_Emitter.pReverbCurve = (X3DAUDIO_DISTANCE_CURVE*)&Emitter_Reverb_Curve;
	m_Emitter.CurveDistanceScaler = 14.0f;
	m_Emitter.DopplerScaler = 1.0f;

}

CEmitterComponent::~CEmitterComponent()
{
}

//void hoge(int* pOut)
//{
//	*pOut = 3;
//	int* p;
//	p = pOut;
//	*p = 3;
//	int i;
//	i = *pOut;
//	i = 2;
//}

void CEmitterComponent::Init(IXAudio2SourceVoice** voice,D3DXMATRIX* matrix)
{
	// マトリクスの登録
	m_EmitterMatrix = matrix;

	m_Voice = *voice;
}

//-----------------------------------------------------------------
//
//	ComponentUpdate
//		位置情報の更新
//
void CEmitterComponent::ComponentUpdate()
{
	D3DXVECTOR3 Pos    = {m_EmitterMatrix->_41,m_EmitterMatrix->_42,m_EmitterMatrix->_43};
	D3DXVECTOR3 forvec = { m_EmitterMatrix->_31,m_EmitterMatrix->_32,m_EmitterMatrix->_33};
	D3DXVECTOR3 upvec  = { m_EmitterMatrix->_21,m_EmitterMatrix->_22,m_EmitterMatrix->_23 };

	m_Emitter.OrientFront	= forvec;
	m_Emitter.OrientTop		= upvec;
	m_Emitter.Position		= Pos;
	m_Emitter.Velocity		= D3DXVECTOR3(0, 0, 0);

	m_X3DDsp = GetX3DSoundMgr()->Calc3DSound(m_Emitter);

	m_Voice->SetOutputMatrix( GetXAudio2Mgr()->GertXAudioMasterVoice() ,1, GetXAudio2Mgr()->GetDeviceDetails().OutputFormat.Format.nChannels ,m_X3DDsp.pMatrixCoefficients);
	m_Voice->SetFrequencyRatio(m_X3DDsp.DopplerFactor);
}