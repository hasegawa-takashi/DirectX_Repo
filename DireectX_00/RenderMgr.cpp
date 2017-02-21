#include "RenderMgr.h"
#include <functional>


//=============================================================================
//
//	�`�����̏�����
//
//=============================================================================
void CRenderMgr::Init()
{
	//-------- ��������R�c�֘A
	// �r���[�}�g���b�N�X�ݒ�
	D3DXMatrixLookAtLH(&m_MatView,
		&D3DXVECTOR3(0.0f, 10.0f, -30.0f),		// ���_���W
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),			// �����_���W
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));		// �A�b�v�x�N�g��
	GetDxMgr()->GetDxDevice()->SetTransform(D3DTS_VIEW, &m_MatView);

	// �v���W�F�N�V�����}�g���b�N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&m_MatProj, D3DXToRadian(FOVY),
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_CLIP, FAR_CLIP);
	GetDxMgr()->GetDxDevice()->SetTransform(D3DTS_PROJECTION, &m_MatProj);

	// �}�e���A���̐ݒ�
	D3DMATERIAL9	mtrl;				// �}�e���A���I�u�W�F�N�g
	ZeroMemory(&mtrl, sizeof(mtrl));	// ��������[���ŃN���A
	mtrl.Diffuse.r = mtrl.Diffuse.g = mtrl.Diffuse.b = mtrl.Diffuse.a = 1.0f;
	mtrl.Ambient = mtrl.Diffuse;
	GetDxMgr()->GetDxDevice()->SetMaterial(&mtrl);

	D3DXVECTOR3	vecDir;					// �������w�肷��x�N�g��
	D3DLIGHT9	light;					// ���C�g�I�u�W�F�N�g
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;	// ���s����
	light.Diffuse.r = light.Diffuse.g = light.Diffuse.b = light.Diffuse.a = 1.0f;
	light.Ambient.r = light.Ambient.g = light.Ambient.b = light.Ambient.a = 0.2f;
	light.Specular = light.Diffuse;
	vecDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f);					// ���̌��������߂�
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);	// ���K�������x�N�g����Ԃ�
	GetDxMgr()->GetDxDevice()->SetLight(0, &light);
	GetDxMgr()->GetDxDevice()->LightEnable(0, TRUE);	// ���C�g0��L��
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// ���ʔ��˂�L��

	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);

	GetDxMgr()->GetDxDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	GetDxMgr()->GetDxDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	GetDxMgr()->GetDxDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	GetDxMgr()->GetDxDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	GetDxMgr()->GetDxDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	GetDxMgr()->GetDxDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

	GetDxMgr()->GetDxDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	GetDxMgr()->GetDxDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//=============================================================================
//
//	�`��O�̏���
//
//=============================================================================
void CRenderMgr::RenderTransStart()
{
	// ���߂����
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

//=============================================================================
//
//	�`��̏I��
//
//=============================================================================
void CRenderMgr::RenderEnd()
{
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	GetDxMgr()->GetDxDevice()->EndScene();
}

