#pragma once
#include"includeheader.h"
#include"TitleHeader.h"

class CGameLoop
{
public:
	CGameLoop();
	~CGameLoop();

	void Init();

	void Reboot();

	void Run();

	void Release();

private:
	
	MSG m_Message;
};

