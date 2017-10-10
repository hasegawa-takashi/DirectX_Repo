#include "X3DSound.h"

//------------------------------------------------------------------------------------------------------------------------------//
//================================================-
//
//	CX3DSound
//
//=================================================
CX3DSound::CX3DSound()
{
	// 3DSound‚Ì‰Šú‰»
	X3DAudioInitialize( GetXAudio2Mgr()->GetDeviceDetails().OutputFormat.dwChannelMask, X3DAUDIO_SPEED_OF_SOUND, m_X3DInstance);

	// DSPSetteing‚ÌÝ’è
	m_X3DDsp = { 0 };
	m_X3DDsp.SrcChannelCount = 1;
	m_X3DDsp.DstChannelCount = 2;
	m_X3DDsp.pMatrixCoefficients = m_matrix;

}

CX3DSound::~CX3DSound()
{
}

bool CX3DSound::SetListener(D3DXMATRIX* posmatrix)
{

	m_Listener = posmatrix;

	D3DXVECTOR3 Pos		= { m_Listener->_41,m_Listener->_42,m_Listener->_43 };
	D3DXVECTOR3 forvec	= { m_Listener->_31,m_Listener->_32,m_Listener->_33 };
	D3DXVECTOR3 upvec	= { m_Listener->_21,m_Listener->_22,m_Listener->_23 };

	m_X3DListener.OrientFront = forvec;
	m_X3DListener.OrientTop = upvec;
	m_X3DListener.pCone = NULL;
	m_X3DListener.Position = Pos;

	m_X3DListener.Velocity = D3DXVECTOR3(0, 0, 0);

	return true;
}

X3DAUDIO_DSP_SETTINGS CX3DSound::Calc3DSound(X3DAUDIO_EMITTER emitter)
{
	if (m_Listener == NULL)
		return m_X3DDsp;

	SetListener(m_Listener);

	X3DAudioCalculate(m_X3DInstance,&m_X3DListener, &emitter, X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER | X3DAUDIO_CALCULATE_LPF_DIRECT | X3DAUDIO_CALCULATE_REVERB, &m_X3DDsp);

	return m_X3DDsp;
}
//------------------------------------------------------------------------------------------------------------------------------//