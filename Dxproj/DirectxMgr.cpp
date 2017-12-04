#include "DirectxMgr.h"



CDirectxMgr::CDirectxMgr()
{
}


CDirectxMgr::~CDirectxMgr()
{
	if (m_D3DDevice != NULL)
	{// デバイスオブジェクトの開放
		m_D3DDevice->Release();
		m_D3DDevice = NULL;
	}

	if (m_D3D9 != NULL)
	{// Direct3Dオブジェクトの開放
		m_D3D9->Release();
		m_D3D9 = NULL;
	}
}

bool CDirectxMgr::CreateDxDevice()
{
	m_D3D9 = NULL;
	m_D3DDevice = NULL;

	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_D3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_D3D9 == NULL)
	{
		return false;
	}

	// 現在のDispModeの取得
	if (FAILED(m_D3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return false;
	}

	// デバイス情報テーブル
	struct  TCreateDevice {
		D3DDEVTYPE  type;
		DWORD behavior;
	};

	const int MaxDevice = 3;
	const TCreateDevice device[MaxDevice] = {
		{ D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING },	// ハードウェアシェーダを使う
		{ D3DDEVTYPE_HAL, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// HAL
		{ D3DDEVTYPE_REF, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// REF
	};

	// Directx3Dオブジェクトの失敗
	if ((m_D3D9 = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
	{
		return false;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&m_D3DPP, sizeof(m_D3DPP));				// ワークをゼロクリア
	m_D3DPP.BackBufferCount = 1;						// バックバッファの数
	m_D3DPP.BackBufferWidth = 800;						// ゲーム画面サイズ(幅)
	m_D3DPP.BackBufferHeight = 600;						// ゲーム画面サイズ(高さ)
	m_D3DPP.BackBufferFormat = d3ddm.Format;			// バックバッファフォーマットはディスプレイモードに合わせて使う
	m_D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;			// 映像信号に同期してフリップする
	m_D3DPP.Windowed = CWindowCreate::Getintance().GetWindowMode();						// ウィンドウモード
	m_D3DPP.EnableAutoDepthStencil = true;				// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	m_D3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;		// デプスバッファとして16bitを使う

	if (CWindowCreate::Getintance().GetWindowMode())
	{// ウィンドウモード
		m_D3DPP.BackBufferFormat = D3DFMT_UNKNOWN;				// バックバッファ
		m_D3DPP.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		m_D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		m_D3DPP.BackBufferFormat = D3DFMT_X8R8G8B8;				// バックバッファ
		m_D3DPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		m_D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}


	int Dev = 0;

	for (Dev = 0; Dev < MaxDevice; Dev++) {
		if (SUCCEEDED(m_D3D9->CreateDevice(D3DADAPTER_DEFAULT, device[Dev].type, CWindowCreate::Getintance().GethwndDevice(),	// デバイスを作成
			device[Dev].behavior, &m_D3DPP, &m_D3DDevice)))
		{
			break;
		}
	}


	if (Dev >= MaxDevice) {
		return false;
	}

	return true;
}