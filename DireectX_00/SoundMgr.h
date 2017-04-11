#pragma once

#include<XAudio2.h>

class CSoundMgr
{
public:
	CSoundMgr();
	~CSoundMgr();

private:
	bool CreateXAudio();
	void FormatWaveTex();

	
private: // ïœêî
	IXAudio2* m_pXAudio;
	HRESULT hr;
	IXAudio2MasteringVoice* m_pMasterVoice;
	IXAudio2SourceVoice* Voice;
	UINT32 m_devicecnt;

	WAVEFORMATEX m_wfx;


};

