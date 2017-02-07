#include "Window.h"

//=============================================================================
//
// Window����[Window.h]
//
//=============================================================================


#define CLASS_NAME  _T("DX22")	//�E�C���h�E�̃N���X��
#define WINDOW_NAME _T("DX22")	//�E�C���h�E�̃L���v�V������

//=============================================================================
// �C���N���[�h
//=============================================================================
#include"Window.h"

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���錾
//=============================================================================

//=============================================================================
//
//	�E�C���h�E�v���V�[�W���|�C���^
//	
//=============================================================================
void CWindow::SetProcPointer(HWND hWnd)
{
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)this);
}
//=============================================================================
//
//	�E�C���h�E�v���V�[�W���Ăяo��
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
//	�v���V�[�W���[���C������
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
//	�E�C���h�E�̐����{����������
//
//=============================================================================
HRESULT CWindow::MakeWin(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ϐ�������
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

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
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

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X���e�[�u��
	struct TCreateDevice {
		D3DDEVTYPE	type;			// �f�o�C�X�̎��
		DWORD		behavior;		// �f�o�C�X�̓���
	};
	const int c_nMaxDevice = 3;
	const TCreateDevice device[c_nMaxDevice] = {
		{ D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING },	// �n�[�h�E�F�A�V�F�[�_���g��
		{ D3DDEVTYPE_HAL, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// HAL
		{ D3DDEVTYPE_REF, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// REF
	};

	int		nDev;			// �f�o�C�X��ʃJ�E���^

	// Direct3D�I�u�W�F�N�g�𐶐�
	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL) {
		MessageBox(_T("g_pD3D�����ł���"));
		return false;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;				// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = bWinmode;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = true;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	bWinmode = false;
	//int nID = MessageBox(_T("�E�B���h�E���[�h�Ŏ��s���܂����H"), _T("��ʃ��[�h"), MB_YESNOCANCEL);
	//if (nID = IDYES)bWinmode = true;

	if (bWinmode)
	{// �E�B���h�E���[�h
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;				// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;				// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	//if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
	//	D3DDEVTYPE_HAL,
	//	hWnd,
	//	D3DCREATE_HARDWARE_VERTEXPROCESSING,
	//	&d3dpp, &g_pD3DDevice)))
	//{
	//	// ��L�̐ݒ肪���s������
	//	// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
	//	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
	//		D3DDEVTYPE_HAL,
	//		hWnd,
	//		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
	//		&d3dpp, &g_pD3DDevice)))
	//	{
	//		// ��L�̐ݒ肪���s������
	//		// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
	//		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
	//			D3DDEVTYPE_REF,
	//			hWnd,
	//			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
	//			&d3dpp, &g_pD3DDevice)))
	//		{
	//			// ���������s
	//			return E_FAIL;
	//		}
	//	}
	//}

	// �f�o�C�X�I�u�W�F�N�g���쐬
	for (nDev = 0; nDev < c_nMaxDevice; nDev++) {
		if (SUCCEEDED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, device[nDev].type, hWnd,	// �f�o�C�X���쐬
			device[nDev].behavior, &d3dpp, &g_pD3DDevice))) break;
	}

	if (nDev >= c_nMaxDevice) {
		return E_FAIL;
	}

	// ���\���p�t�H���g��ݒ�
	/*D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);*/

	//-------- ��������R�c�֘A
	// �r���[�}�g���b�N�X�ݒ�
	D3DXMatrixLookAtLH(&m_MatView,
		//						&D3DXVECTOR3(m_nWidth / 2.0f, 0.0f, //-1000.0f),// ���_���W
		//							-(m_nHeight / 2) / tanf(D3DXToRadian(FOVY) / 2)),
		&D3DXVECTOR3(0.0f, 10.0f, -30.0f),		// ���_���W
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �����_���W
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));		// �A�b�v�x�N�g��
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_MatView);

	// �v���W�F�N�V�����}�g���b�N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&m_MatProj, D3DXToRadian(FOVY),
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_CLIP, FAR_CLIP);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_MatProj);

	// �}�e���A���̐ݒ�
	D3DMATERIAL9	mtrl;				// �}�e���A���I�u�W�F�N�g
	ZeroMemory(&mtrl, sizeof(mtrl));	// ��������[���ŃN���A
	mtrl.Diffuse.r = mtrl.Diffuse.g = mtrl.Diffuse.b = mtrl.Diffuse.a = 1.0f;
	mtrl.Ambient = mtrl.Diffuse;
	g_pD3DDevice->SetMaterial(&mtrl);

	D3DXVECTOR3	vecDir;					// �������w�肷��x�N�g��
	D3DLIGHT9	light;					// ���C�g�I�u�W�F�N�g
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;	// ���s����
	light.Diffuse.r = light.Diffuse.g = light.Diffuse.b = light.Diffuse.a = 1.0f;
	light.Ambient.r = light.Ambient.g = light.Ambient.b = light.Ambient.a = 0.2f;
	light.Specular = light.Diffuse;
	vecDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f);					// ���̌��������߂�
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);	// ���K�������x�N�g����Ԃ�
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, TRUE);	// ���C�g0��L��
	g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// ���ʔ��˂�L��

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

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);



	return S_OK;

}

//=============================================================================
//
//	�I������
//
//=============================================================================
void CWindow::ReleaseWin(HINSTANCE hInstance )
{
	UnregisterClass(CLASS_NAME, hInstance);

	if (g_pD3DDevice != NULL)
	{// �f�o�C�X�I�u�W�F�N�g�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}


	delete cWnd;
}

//=============================================================================
// ���b�Z�[�W �{�b�N�X�̕\��
//	in :	pszText		���b�Z�[�W �{�b�N�X�̃e�L�X�g�̃A�h���X
//			pszCaption	���b�Z�[�W �{�b�N�X�̃^�C�g���̃A�h���X
//			nType		���b�Z�[�W �{�b�N�X�̃X�^�C��
//	out:	�����ꂽ�{�^��
//=============================================================================
int CWindow::MessageBox(LPCTSTR pszText, LPCTSTR pszCaption, UINT nType)
{
	return ::MessageBox(hWnd, pszText, pszCaption, nType);
}