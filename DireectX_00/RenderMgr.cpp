#include "RenderMgr.h"
#include <functional>


//=============================================================================
//
//	描画周りの初期化
//
//=============================================================================
void CRenderMgr::Init()
{
	//-------- ここから３Ｄ関連
	// ビューマトリックス設定
	D3DXMatrixLookAtLH(&m_MatView,
		&D3DXVECTOR3(0.0f, 10.0f, -30.0f),		// 視点座標
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),			// 注視点座標
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));		// アップベクトル
	GetDxMgr()->GetDxDevice()->SetTransform(D3DTS_VIEW, &m_MatView);

	// プロジェクションマトリックス設定
	D3DXMatrixPerspectiveFovLH(&m_MatProj, D3DXToRadian(FOVY),
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_CLIP, FAR_CLIP);
	GetDxMgr()->GetDxDevice()->SetTransform(D3DTS_PROJECTION, &m_MatProj);

	// マテリアルの設定
	D3DMATERIAL9	mtrl;				// マテリアルオブジェクト
	ZeroMemory(&mtrl, sizeof(mtrl));	// いったんゼロでクリア
	mtrl.Diffuse.r = mtrl.Diffuse.g = mtrl.Diffuse.b = mtrl.Diffuse.a = 1.0f;
	mtrl.Ambient = mtrl.Diffuse;
	GetDxMgr()->GetDxDevice()->SetMaterial(&mtrl);

	D3DXVECTOR3	vecDir;					// 方向を指定するベクトル
	D3DLIGHT9	light;					// ライトオブジェクト
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;	// 平行光源
	light.Diffuse.r = light.Diffuse.g = light.Diffuse.b = light.Diffuse.a = 1.0f;
	light.Ambient.r = light.Ambient.g = light.Ambient.b = light.Ambient.a = 0.2f;
	light.Specular = light.Diffuse;
	vecDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f);					// 光の向きを決める
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);	// 正規化したベクトルを返す
	GetDxMgr()->GetDxDevice()->SetLight(0, &light);
	GetDxMgr()->GetDxDevice()->LightEnable(0, TRUE);	// ライト0を有効
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// 鏡面反射を有効

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
//	描画前の準備
//
//=============================================================================
void CRenderMgr::RenderTransStart()
{
	// 透過する方
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

//=============================================================================
//
//	描画の終了
//
//=============================================================================
void CRenderMgr::RenderEnd()
{
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	GetDxMgr()->GetDxDevice()->EndScene();
}

