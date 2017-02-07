#pragma once
#include"Window.h"
#include"Debug.h"

class CFPS
{
private:
#ifdef _DEBUG
	int					g_nCountFPS;			// FPSƒJƒEƒ“ƒ^
	
#endif
	
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	

	CFPS(void);
public:

	static CFPS* Instance(){
		static CFPS _Instance;
		return &_Instance;
	}

	void Init();

	void Update();

	void Draw();

	void Release();

	void FpsCntUp();

	int SetFps();

	~CFPS(void);
};

