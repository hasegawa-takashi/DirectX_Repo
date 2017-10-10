#include "RenderFormat.h"



CRenderFormat::CRenderFormat()
{
}


CRenderFormat::~CRenderFormat()
{
}

void CRenderFormat::Init()
{
	D3DXMatrixLookAtLH(&m_MatView,
		&D3DXVECTOR3(0.0f, 10.0f, -30.0f),		// ���_���W
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),			// �����_���W
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));		// �A�b�v�x�N�g��
	CDirectxMgr::Getintance().GetDxDevice()->SetTransform(D3DTS_VIEW, &m_MatView);

	// TODO :: �����̐ݒ肪�}�W�b�N�i���o
	D3DXMatrixPerspectiveFovLH(&m_MatProj, D3DXToRadian(FOVY),
		CWindowCreate::Getintance().GetASPECT(), NEAR_CLIP, FAR_CLIP);
	CDirectxMgr::Getintance().GetDxDevice()->SetTransform(D3DTS_PROJECTION, &m_MatProj);

	D3DMATERIAL9	mtrl;				// �}�e���A���I�u�W�F�N�g
	ZeroMemory(&mtrl, sizeof(mtrl));	// ��������[���ŃN���A
	mtrl.Diffuse.r = mtrl.Diffuse.g = mtrl.Diffuse.b = mtrl.Diffuse.a = 1.0f;
	mtrl.Ambient = mtrl.Diffuse;

	CDirectxMgr::Getintance().GetDxDevice()->SetMaterial(&mtrl);

	D3DXVECTOR3	vecDir;					// �������w�肷��x�N�g��
	D3DLIGHT9	light;					// ���C�g�I�u�W�F�N�g
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;	// ���s����
	light.Diffuse.r = light.Diffuse.g = light.Diffuse.b = light.Diffuse.a = 1.0f;
	light.Ambient.r = light.Ambient.g = light.Ambient.b = light.Ambient.a = 0.2f;
	light.Specular = light.Diffuse;
	vecDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f);					// ���̌��������߂�
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);	// ���K�������x�N�g����Ԃ�

	CDirectxMgr::Getintance().GetDxDevice()->SetLight(0, &light);
	CDirectxMgr::Getintance().GetDxDevice()->LightEnable(0, TRUE);	// ���C�g0��L��
	CDirectxMgr::Getintance().GetDxDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// ���ʔ��˂�L��
	CDirectxMgr::Getintance().GetDxDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	CDirectxMgr::Getintance().GetDxDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	CDirectxMgr::Getintance().GetDxDevice()->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
	CDirectxMgr::Getintance().GetDxDevice()->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
	CDirectxMgr::Getintance().GetDxDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	CDirectxMgr::Getintance().GetDxDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	CDirectxMgr::Getintance().GetDxDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	CDirectxMgr::Getintance().GetDxDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	CDirectxMgr::Getintance().GetDxDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	CDirectxMgr::Getintance().GetDxDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	CDirectxMgr::Getintance().GetDxDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	CDirectxMgr::Getintance().GetDxDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

}

void CRenderFormat::TransmissionDraw()
{
	CDirectxMgr::Getintance().GetDxDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CDirectxMgr::Getintance().GetDxDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CDirectxMgr::Getintance().GetDxDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	CDirectxMgr::Getintance().GetDxDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

bool CRenderFormat::StartRender()
{
	CDirectxMgr::Getintance().GetDxDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(128, 128, 255), 1.0f, 0);

	if (SUCCEEDED(CDirectxMgr::Getintance().GetDxDevice()->BeginScene()))
	{
		return true;
	}

	return false;

}

void CRenderFormat::EndRender()
{
	CDirectxMgr::Getintance().GetDxDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	CDirectxMgr::Getintance().GetDxDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	CDirectxMgr::Getintance().GetDxDevice()->EndScene();
	CDirectxMgr::Getintance().GetDxDevice()->Present(NULL, NULL, NULL, NULL);

}