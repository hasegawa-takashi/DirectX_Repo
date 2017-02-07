#include "FPS.h"
#include"Debug.h"

CFPS::CFPS()
{
}


CFPS::~CFPS()
{
}

void CFPS::Init()
{
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();
	dwCurrentTime =
		dwFrameCount = 0;

#ifdef _DEBUG
	
#endif

}

void CFPS::Update()
{
	dwCurrentTime = timeGetTime();
	if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
	{
#ifdef _DEBUG
		g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
		dwFPSLastTime = dwCurrentTime;
		dwFrameCount = 0;
	}

}

void CFPS::Draw()
{

	// �f�o�b�N�p�̏�������
#ifdef _DEBUG
	CDebug::Instance()->Conversion(_T("\nFPS::"), g_nCountFPS);

#endif

	// ���̂ق��������邩�ȁH

}

void CFPS::Release()
{

}

void CFPS::FpsCntUp()
{
	dwExecLastTime = dwCurrentTime;
	dwFrameCount++;
}

int CFPS::SetFps()
{
	return (dwCurrentTime - dwExecLastTime);
}