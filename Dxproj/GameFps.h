#pragma once
#include"includeheader.h"

class CGameFps : public CSingleton<CGameFps>
{
public:
	CGameFps();
	~CGameFps();

	void Update();

	bool GetUpdatetiming();

private:

	DWORD m_ExecLasttime;
	DWORD m_FpsLastTime;
	DWORD m_CurrentTime;
	DWORD m_FrameCount;

};

