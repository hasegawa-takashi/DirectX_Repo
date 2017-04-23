#pragma once

#include<XAudio2.h>
#include <iostream>

class CXAudio2Interface
{
public:
	/*static CXAudio2Interface* Instance()
	{
		static CXAudio2Interface _Instance;
		return &_Instance;
	}*/

	~CXAudio2Interface();
	CXAudio2Interface();

	bool CreateXAudio();

	bool SetXAudio2SouceVoice(IXAudio2SourceVoice**,WAVEFORMATEX*);

private:


	IXAudio2* m_XAudio2;
	IXAudio2MasteringVoice* m_MasterVoice;

	UINT32 flags = 0;

	UINT32 m_devicecnt;
};

