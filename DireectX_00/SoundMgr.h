#pragma once

#include<XAudio2.h>
#include"LoadWave.h"

class CSoundMgr
{
public:
	CSoundMgr();
	~CSoundMgr();

	void WaveFileLoad(const char filepath);

private:

	bool CreateXAudio();
	

	
private: // ïœêî
	IXAudio2* m_pXAudio;
	HRESULT hr;
	IXAudio2MasteringVoice* m_pMasterVoice;
	IXAudio2SourceVoice* Voice;
	UINT32 m_devicecnt;

	CLoadWave *wave;
	WAVEFORMATEX wavefmt;
};

