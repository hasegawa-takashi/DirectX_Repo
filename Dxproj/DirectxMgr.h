#pragma once

#include"includeheader.h"

class CDirectxMgr : public CSingleton<CDirectxMgr>
{
public:
	CDirectxMgr();
	~CDirectxMgr();

	
	// デバイスの初期設定
	bool CreateDxDevice();

	LPDIRECT3DDEVICE9 GetDxDevice() { return m_D3DDevice; }
private:
	LPDIRECT3D9 m_D3D9;				// Directx3Dオブジェクト
	LPDIRECT3DDEVICE9 m_D3DDevice;	// デバイスオブジェクト
	D3DPRESENT_PARAMETERS m_D3DPP;	// 画面情報の設定

};

