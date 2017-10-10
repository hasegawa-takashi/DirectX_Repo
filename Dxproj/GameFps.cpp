#include "GameFps.h"



CGameFps::CGameFps()
{

	m_ExecLasttime = m_FpsLastTime = timeGetTime();
	m_CurrentTime = m_FrameCount = 0;

}


CGameFps::~CGameFps()
{
}

void CGameFps::Update()
{
	m_CurrentTime = timeGetTime();
	if ((m_CurrentTime - m_FpsLastTime) >= 500)
	{
		m_FpsLastTime = m_CurrentTime;
		m_FrameCount = 0;
	}

	// カウントアップ

}

bool CGameFps::GetUpdatetiming()
{
	DWORD _fps = m_CurrentTime - m_ExecLasttime;

	if (_fps >= (1000 / 60))
	{

		m_ExecLasttime = m_CurrentTime;
		m_FrameCount++;

		return true;
	}

	return false;

}