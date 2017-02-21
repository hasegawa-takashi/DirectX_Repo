#pragma once
//=============================================================================
//	インクルード
//=============================================================================
#include"Window.h"
#include<d3dx9.h>

//=============================================================================
// ライブラリのリンク
//=============================================================================
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")

//=============================================================================
// class定義
//=============================================================================

class CDxDevice
{
private:
	LPDIRECT3D9 D3D;				// Directx3Dオブジェクト
	LPDIRECT3DDEVICE9 D3DDevice;	// デバイスオブジェクト
	D3DPRESENT_PARAMETERS D3DPP;	// 画面情報の設定

public:
	
	CDxDevice();
	~CDxDevice();

	// Directxのsingleton
	static CDxDevice* Instance() {
		static CDxDevice _Instance;
		return &_Instance;
	}

	// Graphicデバイスのゲッター
	const LPDIRECT3DDEVICE9 GetDxDevice() { return D3DDevice; }

	// デバイスの初期設定
	bool CreateDxDevice();

};

//=============================================================================
// デバイス呼び出し用
//=============================================================================
inline CDxDevice* GetDxMgr()
{
	return CDxDevice::Instance();
}

