#include "WindowCreate.h"

CWindowCreate::CWindowCreate()
{
}


CWindowCreate::~CWindowCreate()
{
}


HRESULT CWindowCreate::InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	m_Winmode = true;
	m_hInstance = hInstance;

	WNDCLASSEX _wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		CWindowCreate::WndProc,
		0,0,
		hInstance,
		0,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	// ウィンドウクラスの登録
	RegisterClassEx(&_wcex);

	// ウィンドウの作成
	m_hWnd = CreateWindowEx(0,
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
		(LPVOID)this);

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return S_OK;

}

void CWindowCreate::ReleaseWindow()
{
	UnregisterClass(CLASS_NAME, m_hInstance);
}

void CWindowCreate::SetProcPointer(HWND hWnd)
{
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)this);
}

LRESULT CALLBACK CWindowCreate::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CWindowCreate* thisPtr = (CWindowCreate*)GetWindowLong(hWnd, GWL_USERDATA);

	if (!thisPtr)
	{
		if (uMsg == WM_CREATE)
			thisPtr = (CWindowCreate*)((LPCREATESTRUCT)lParam)->lpCreateParams;

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

LRESULT CWindowCreate::MainProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
