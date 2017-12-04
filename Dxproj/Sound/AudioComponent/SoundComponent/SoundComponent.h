#pragma once


#include"..\..\Sound.h"

/**
*	�T�E���hComponent�̐e
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

