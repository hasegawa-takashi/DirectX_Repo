#pragma once

using namespace std;

// ------------------------------
// --- グローバル定数宣言


#include<Windows.h>
#include<tchar.h>
#include<iostream>
#include<thread>
#include<mutex>
#include<assert.h>
#include<list>
#include<vector>
#include<string>
#include<array>
#include<time.h>
#include<math.h>
#include<d3dx9.h>
#include<XAudio2.h>
#include<X3DAudio.h>

// Funcフォルダ
#include"Singleton.h"
#include"WindowCreate.h"
#include"DirectxMgr.h"
#include"SceneMgr.h"
#include"ObjMgr.h"
#include"GameFps.h"
#include"GameLoop.h"
#include"RenderFormat.h"
#include"Input.h"
#include"Calculation.h"
#include"Sound\Sound.h"
#include"Camera.h"
#include"Debug.h"


#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment(lib,"X3daudio.lib")

// -------------------------------------
// --- SAFE_DELETEの代わり
template <class T>
inline void Complete_type_safe_delete(T*& p)
{
	typedef char _type_must_be_complete[sizeof(T) ? 1 : -1];
	(void)sizeof(_type_must_be_complete);

	delete p;
	p = nullptr;
}