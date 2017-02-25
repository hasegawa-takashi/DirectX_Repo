#include"DxDevice.h"
#include<tchar.h>

//=============================================================================
//
//	�R���X�g���N�^
//
//=============================================================================
CDxDevice::CDxDevice()
{
}

//=============================================================================
//
//	�f�X�g
//
//=============================================================================
CDxDevice::~CDxDevice()
{
	// �f�X�g���N�^�ŉ��

	if (D3DDevice != NULL)
	{// �f�o�C�X�I�u�W�F�N�g�̊J��
		D3DDevice->Release();
		D3DDevice = NULL;
	}

	if (D3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		D3D->Release();
		D3D = NULL;
	}

}

//=============================================================================
//
//	Directx9�f�o�C�X�̍쐬
//
//=============================================================================
bool CDxDevice::CreateDxDevice()
{

	D3D = NULL;
	D3DDevice = NULL;

	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	D3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (D3D == NULL)
	{
		GetWinMgr()->MessageBox(_T("Directx�̍쐬�Ɏ��s"));
		return false;
	}

	// ���݂�DispMode�̎擾
	if (FAILED(D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		GetWinMgr()->MessageBox(_T("DisPlay���[�h�̎擾�Ɏ��s"));
		return false;
	}

	// �f�o�C�X���e�[�u��
	struct  TCreateDevice{
		D3DDEVTYPE  type;
		DWORD behavior;
	};

	const int MaxDevice = 3;
	const TCreateDevice device[MaxDevice] = {
		{ D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING },	// �n�[�h�E�F�A�V�F�[�_���g��
		{ D3DDEVTYPE_HAL, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// HAL
		{ D3DDEVTYPE_REF, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// REF
	};

	// Directx3D�I�u�W�F�N�g�̎��s
	if ( (D3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
	{
		CWindow::Instance()->MessageBox(_T("g_pD3D�����ł���"));
		return false;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&D3DPP, sizeof(D3DPP));				// ���[�N���[���N���A
	D3DPP.BackBufferCount = 1;						// �o�b�N�o�b�t�@�̐�
	D3DPP.BackBufferWidth = SCREEN_WIDTH;			// �Q�[����ʃT�C�Y(��)
	D3DPP.BackBufferHeight = SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	D3DPP.BackBufferFormat = d3ddm.Format;			// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
	D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
	D3DPP.Windowed = GetWinMgr()->GetWindowMode();						// �E�B���h�E���[�h
	D3DPP.EnableAutoDepthStencil = true;			// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	D3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;	// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if (GetWinMgr()->GetWindowMode())
	{// �E�B���h�E���[�h
		D3DPP.BackBufferFormat = D3DFMT_UNKNOWN;				// �o�b�N�o�b�t�@
		D3DPP.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		D3DPP.BackBufferFormat = D3DFMT_X8R8G8B8;				// �o�b�N�o�b�t�@
		D3DPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}


	int Dev = 0;

	for (Dev = 0; Dev < MaxDevice; Dev++) {
		if (SUCCEEDED(D3D->CreateDevice(D3DADAPTER_DEFAULT, device[Dev].type, GetWinMgr()->GethwndDevice(),	// �f�o�C�X���쐬
			device[Dev].behavior, &D3DPP, &D3DDevice))) break;
	}


	if (Dev >= MaxDevice) {
		return false;
	}

	return true;
}