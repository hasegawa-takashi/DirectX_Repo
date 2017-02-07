#include "Window.h"

//=============================================================================
//
// Window処理[Window.h]
//
//=============================================================================


#define CLASS_NAME  _T("DX22")	//ウインドウのクラス名
#define WINDOW_NAME _T("DX22")	//ウインドウのキャプション名

//=============================================================================
// インクルード
//=============================================================================
#include"Window.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル宣言
//=============================================================================

//=============================================================================
//
//	ウインドウプロシージャポインタ
//	
//=============================================================================
void CWindow::SetProcPointer(HWND hWnd)
{
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)this);
}
//=============================================================================
//
//	ウインドウプロシージャ呼び出し
//	
//=============================================================================
LRESULT CALLBACK CWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CWindow* thisPtr = (CWindow*)GetWindowLong(hWnd, GWL_USERDATA);

	if (!thisPtr)
	{
		if (uMsg == WM_CREATE)
			thisPtr = (CWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;

		if (thisPtr)
		{
			thisPtr->SetProcPointer(hWnd);
		}

	}

	if (thisPtr)
	{
		LRESULT lResult = thisPtr->MainProc(hWnd, uMsg, wParam, lParam);
		return lResult;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//=============================================================================
//
//	プロシージャーメイン処理
//
//=============================================================================
LRESULT CWindow::MainProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
//
//	ウインドウの生成＋初期化処理
//
//=============================================================================
HRESULT CWindow::MakeWin(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 変数初期化
	bWinmode = TRUE;
	g_pD3D = NULL;
	g_pD3DDevice = NULL;
	cWnd = new CWindow;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		CWindow::WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
		NULL,
		NULL,
		hInstance,
		(LPVOID)cWnd);

	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイス情報テーブル
	struct TCreateDevice {
		D3DDEVTYPE	type;			// デバイスの種類
		DWORD		behavior;		// デバイスの動作
	};
	const int c_nMaxDevice = 3;
	const TCreateDevice device[c_nMaxDevice] = {
		{ D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING },	// ハードウェアシェーダを使う
		{ D3DDEVTYPE_HAL, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// HAL
		{ D3DDEVTYPE_REF, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// REF
	};

	int		nDev;			// デバイス種別カウンタ

	// Direct3Dオブジェクトを生成
	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL) {
		MessageBox(_T("g_pD3D生成できず"));
		return false;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;						// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;				// バックバッファフォーマットはディスプレイモードに合わせて使う
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed = bWinmode;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = true;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// デプスバッファとして16bitを使う

	bWinmode = false;
	//int nID = MessageBox(_T("ウィンドウモードで実行しますか？"), _T("画面モード"), MB_YESNOCANCEL);
	//if (nID = IDYES)bWinmode = true;

	if (bWinmode)
	{// ウィンドウモード
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;				// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;				// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	//if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
	//	D3DDEVTYPE_HAL,
	//	hWnd,
	//	D3DCREATE_HARDWARE_VERTEXPROCESSING,
	//	&d3dpp, &g_pD3DDevice)))
	//{
	//	// 上記の設定が失敗したら
	//	// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
	//	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
	//		D3DDEVTYPE_HAL,
	//		hWnd,
	//		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
	//		&d3dpp, &g_pD3DDevice)))
	//	{
	//		// 上記の設定が失敗したら
	//		// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
	//		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
	//			D3DDEVTYPE_REF,
	//			hWnd,
	//			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
	//			&d3dpp, &g_pD3DDevice)))
	//		{
	//			// 初期化失敗
	//			return E_FAIL;
	//		}
	//	}
	//}

	// デバイスオブジェクトを作成
	for (nDev = 0; nDev < c_nMaxDevice; nDev++) {
		if (SUCCEEDED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, device[nDev].type, hWnd,	// デバイスを作成
			device[nDev].behavior, &d3dpp, &g_pD3DDevice))) break;
	}

	if (nDev >= c_nMaxDevice) {
		return E_FAIL;
	}

	// 情報表示用フォントを設定
	/*D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);*/

	//-------- ここから３Ｄ関連
	// ビューマトリックス設定
	D3DXMatrixLookAtLH(&m_MatView,
		//						&D3DXVECTOR3(m_nWidth / 2.0f, 0.0f, //-1000.0f),// 視点座標
		//							-(m_nHeight / 2) / tanf(D3DXToRadian(FOVY) / 2)),
		&D3DXVECTOR3(0.0f, 10.0f, -30.0f),		// 視点座標
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 注視点座標
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));		// アップベクトル
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_MatView);

	// プロジェクションマトリックス設定
	D3DXMatrixPerspectiveFovLH(&m_MatProj, D3DXToRadian(FOVY),
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_CLIP, FAR_CLIP);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_MatProj);

	// マテリアルの設定
	D3DMATERIAL9	mtrl;				// マテリアルオブジェクト
	ZeroMemory(&mtrl, sizeof(mtrl));	// いったんゼロでクリア
	mtrl.Diffuse.r = mtrl.Diffuse.g = mtrl.Diffuse.b = mtrl.Diffuse.a = 1.0f;
	mtrl.Ambient = mtrl.Diffuse;
	g_pD3DDevice->SetMaterial(&mtrl);

	D3DXVECTOR3	vecDir;					// 方向を指定するベクトル
	D3DLIGHT9	light;					// ライトオブジェクト
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;	// 平行光源
	light.Diffuse.r = light.Diffuse.g = light.Diffuse.b = light.Diffuse.a = 1.0f;
	light.Ambient.r = light.Ambient.g = light.Ambient.b = light.Ambient.a = 0.2f;
	light.Specular = light.Diffuse;
	vecDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f);					// 光の向きを決める
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);	// 正規化したベクトルを返す
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, TRUE);	// ライト0を有効
	g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// 鏡面反射を有効

	g_pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	g_pD3DDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
	g_pD3DDevice->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);



	return S_OK;

}

//=============================================================================
//
//	終了処理
//
//=============================================================================
void CWindow::ReleaseWin(HINSTANCE hInstance )
{
	UnregisterClass(CLASS_NAME, hInstance);

	if (g_pD3DDevice != NULL)
	{// デバイスオブジェクトの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
		g_pD3D = NULL;
	}


	delete cWnd;
}

//=============================================================================
// メッセージ ボックスの表示
//	in :	pszText		メッセージ ボックスのテキストのアドレス
//			pszCaption	メッセージ ボックスのタイトルのアドレス
//			nType		メッセージ ボックスのスタイル
//	out:	押されたボタン
//=============================================================================
int CWindow::MessageBox(LPCTSTR pszText, LPCTSTR pszCaption, UINT nType)
{
	return ::MessageBox(hWnd, pszText, pszCaption, nType);
}