#include"DxDevice.h"
#include<tchar.h>

//=============================================================================
//
//	コンストラクタ
//
//=============================================================================
CDxDevice::CDxDevice()
{
}

//=============================================================================
//
//	デスト
//
//=============================================================================
CDxDevice::~CDxDevice()
{
	// デストラクタで解放

	if (D3DDevice != NULL)
	{// デバイスオブジェクトの開放
		D3DDevice->Release();
		D3DDevice = NULL;
	}

	if (D3D != NULL)
	{// Direct3Dオブジェクトの開放
		D3D->Release();
		D3D = NULL;
	}

}

//=============================================================================
//
//	Directx9デバイスの作成
//
//=============================================================================
bool CDxDevice::CreateDxDevice()
{

	D3D = NULL;
	D3DDevice = NULL;

	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	D3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (D3D == NULL)
	{
		GetWinMgr()->MessageBox(_T("Directxの作成に失敗"));
		return false;
	}

	// 現在のDispModeの取得
	if (FAILED(D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		GetWinMgr()->MessageBox(_T("DisPlayモードの取得に失敗"));
		return false;
	}

	// デバイス情報テーブル
	struct  TCreateDevice{
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
	if ( (D3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
	{
		CWindow::Instance()->MessageBox(_T("g_pD3D生成できず"));
		return false;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&D3DPP, sizeof(D3DPP));				// ワークをゼロクリア
	D3DPP.BackBufferCount = 1;						// バックバッファの数
	D3DPP.BackBufferWidth = SCREEN_WIDTH;			// ゲーム画面サイズ(幅)
	D3DPP.BackBufferHeight = SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	D3DPP.BackBufferFormat = d3ddm.Format;			// バックバッファフォーマットはディスプレイモードに合わせて使う
	D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;		// 映像信号に同期してフリップする
	D3DPP.Windowed = GetWinMgr()->GetWindowMode();						// ウィンドウモード
	D3DPP.EnableAutoDepthStencil = true;			// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	D3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;	// デプスバッファとして16bitを使う

	if (GetWinMgr()->GetWindowMode())
	{// ウィンドウモード
		D3DPP.BackBufferFormat = D3DFMT_UNKNOWN;				// バックバッファ
		D3DPP.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		D3DPP.BackBufferFormat = D3DFMT_X8R8G8B8;				// バックバッファ
		D3DPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}


	int Dev = 0;

	for (Dev = 0; Dev < MaxDevice; Dev++) {
		if (SUCCEEDED(D3D->CreateDevice(D3DADAPTER_DEFAULT, device[Dev].type, GetWinMgr()->GethwndDevice(),	// デバイスを作成
			device[Dev].behavior, &D3DPP, &D3DDevice))) break;
	}


	if (Dev >= MaxDevice) {
		return false;
	}

	return true;
}