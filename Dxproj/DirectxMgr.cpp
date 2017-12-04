#include "DirectxMgr.h"



CDirectxMgr::CDirectxMgr()
{
}


CDirectxMgr::~CDirectxMgr()
{
	if (m_D3DDevice != NULL)
	{// �f�o�C�X�I�u�W�F�N�g�̊J��
		m_D3DDevice->Release();
		m_D3DDevice = NULL;
	}

	if (m_D3D9 != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		m_D3D9->Release();
		m_D3D9 = NULL;
	}
}

bool CDirectxMgr::CreateDxDevice()
{
	m_D3D9 = NULL;
	m_D3DDevice = NULL;

	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_D3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_D3D9 == NULL)
	{
		return false;
	}

	// ���݂�DispMode�̎擾
	if (FAILED(m_D3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return false;
	}

	// �f�o�C�X���e�[�u��
	struct  TCreateDevice {
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
	if ((m_D3D9 = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
	{
		return false;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&m_D3DPP, sizeof(m_D3DPP));				// ���[�N���[���N���A
	m_D3DPP.BackBufferCount = 1;						// �o�b�N�o�b�t�@�̐�
	m_D3DPP.BackBufferWidth = 800;						// �Q�[����ʃT�C�Y(��)
	m_D3DPP.BackBufferHeight = 600;						// �Q�[����ʃT�C�Y(����)
	m_D3DPP.BackBufferFormat = d3ddm.Format;			// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
	m_D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;			// �f���M���ɓ������ăt���b�v����
	m_D3DPP.Windowed = CWindowCreate::Getintance().GetWindowMode();						// �E�B���h�E���[�h
	m_D3DPP.EnableAutoDepthStencil = true;				// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	m_D3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;		// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if (CWindowCreate::Getintance().GetWindowMode())
	{// �E�B���h�E���[�h
		m_D3DPP.BackBufferFormat = D3DFMT_UNKNOWN;				// �o�b�N�o�b�t�@
		m_D3DPP.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		m_D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		m_D3DPP.BackBufferFormat = D3DFMT_X8R8G8B8;				// �o�b�N�o�b�t�@
		m_D3DPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		m_D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}


	int Dev = 0;

	for (Dev = 0; Dev < MaxDevice; Dev++) {
		if (SUCCEEDED(m_D3D9->CreateDevice(D3DADAPTER_DEFAULT, device[Dev].type, CWindowCreate::Getintance().GethwndDevice(),	// �f�o�C�X���쐬
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