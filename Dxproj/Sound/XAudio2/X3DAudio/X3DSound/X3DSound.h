#pragma once

#include"../../../Sound.h"
#include"../../../../Calculation.h"
#include"../../../XAudio2/XAudio2Interface/XAudioInterface.h"

#pragma comment(lib,"X3daudio.lib")
//------------------------------------------------------------
//
//	3DSoundä«óùé“
//
//------------------------------------------------------------
class CX3DSound
{
public:
	static CX3DSound* Instance()
	{
		static CX3DSound _Instance;
		return &_Instance;
	}

	~CX3DSound();

	bool SetListener(D3DXMATRIX* matrix);

	X3DAUDIO_DSP_SETTINGS Calc3DSound(X3DAUDIO_EMITTER emitter);

private:
	CX3DSound();

	X3DAUDIO_HANDLE			m_X3DInstance;
	X3DAUDIO_DSP_SETTINGS	m_X3DDsp;
	
	D3DXMATRIX*				m_Listener;
	X3DAUDIO_LISTENER		m_X3DListener;
	FLOAT32					m_matrix[6];
};

inline CX3DSound* GetX3DSoundMgr()
{
	return CX3DSound::Instance();
}
