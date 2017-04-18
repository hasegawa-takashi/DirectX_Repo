#pragma once

#include<XAudio2.h>
#include <mmsystem.h>

#include"LoadWave.h"

class CBGM;

class CSoundMgr
{
public:
	static CSoundMgr* Instance() {
	static CSoundMgr _Instance;
	return &_Instance;
	}

	void SetMasterVolume(float Vol);	// �S�̉����̐ݒ�
	float GetMasterVolume();			// �S�̉����̎擾

	CSoundMgr();
	~CSoundMgr();



	void SetSourcevoice(IXAudio2SourceVoice**,WAVEFORMATEX*);

	void InitSoundMgr();

	void Play(int bgm);

private:

	bool CreateXAudio();
	

	
private: // �ϐ�
	IXAudio2* m_pXAudio;
	HRESULT hr;
	IXAudio2MasteringVoice* m_pMasterVoice;
	UINT32 m_devicecnt;

	CBGM* m_BgmVoice;

};


//=============================================================================
// �f�o�C�X�Ăяo���p
//=============================================================================
inline CSoundMgr* GetSoundMgr()
{
	return CSoundMgr::Instance();
}


