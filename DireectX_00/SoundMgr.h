#pragma once

#include<XAudio2.h>
#include"LoadWave.h"

class CSoundMgr
{
public:
	CSoundMgr();
	~CSoundMgr();


	void SetSourcevoice(IXAudio2SourceVoice*,WAVEFORMATEX);

	static CSoundMgr* Instance() {
		static CSoundMgr _Instance;
		return &_Instance;
	}



private:

	bool CreateXAudio();
	

	
private: // �ϐ�
	IXAudio2* m_pXAudio;
	HRESULT hr;
	IXAudio2MasteringVoice* m_pMasterVoice;
	UINT32 m_devicecnt;
};


//=============================================================================
// �f�o�C�X�Ăяo���p
//=============================================================================
inline CSoundMgr* GetSoundMgr()
{
	return CSoundMgr::Instance();
}


