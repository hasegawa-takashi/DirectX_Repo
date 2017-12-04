#pragma once


#include"..\..\Sound.h"

/**
*	サウンドComponentの親
*	
*/
class CSoundComponent
{
public:
	CSoundComponent() : m_Sourcevoice(nullptr) {}
	virtual ~CSoundComponent() {}

	virtual void ComponentUpdate() = 0;

	
protected:
	IXAudio2SourceVoice* m_Sourcevoice;
};

