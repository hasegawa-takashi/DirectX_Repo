#include "Sprite.h"


CSprite::CSprite()
{
}


CSprite::~CSprite()
{
}

void CSprite::Init()
{
	

}

void CSprite::Update()
{


}

void CSprite::Render()
{


	//頂点フォーマット設定
	CWindow::Instance()->GetDevice()->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	if (FAILED(CWindow::Instance()->GetDevice()->SetTexture(0, Spritebox.m_Texture)))
		return;

	//ポリゴン描画
	if (FAILED(CWindow::Instance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &Spritebox.vertex_2d, sizeof(VERTEX_2D))))
	{
		Spritebox.Createflag = false;
		return;
	}

}

void CSprite::Release()
{
	if (Spritebox.Createflag == true)
	{
		Spritebox.m_Texture->Release();
		Spritebox.m_Texture = NULL;
		Spritebox.Createflag = false;
	}
}

HRESULT CSprite::CreateMakeVertex2DPolygon(LPCTSTR  TexFile, float nX, float nY, float Width, float Height, int fade)
{
	HRESULT hr;

	Spritebox.Fade = fade;

	hr = D3DXCreateTextureFromFile(CWindow::Instance()->GetDevice()
		, TexFile
		, &Spritebox.m_Texture);
	
	//頂点座標　※時計回り注意
	Spritebox.vertex_2d[0].pos = D3DXVECTOR3(nX, nY, 0.0f);
	Spritebox.vertex_2d[1].pos = D3DXVECTOR3(nX + Width, nY, 0.0f);
	Spritebox.vertex_2d[2].pos = D3DXVECTOR3(nX, nY + Height, 0.0f);
	Spritebox.vertex_2d[3].pos = D3DXVECTOR3(nX + Width, nY + Height, 0.0f);

	//rhw
	Spritebox.vertex_2d[0].rhw = 1.0f;
	Spritebox.vertex_2d[1].rhw = 1.0f;
	Spritebox.vertex_2d[2].rhw = 1.0f;
	Spritebox.vertex_2d[3].rhw = 1.0f;

	//頂点カラー 
	Spritebox.vertex_2d[0].col = D3DCOLOR_RGBA(255, 255, 255, Spritebox.Fade);
	Spritebox.vertex_2d[1].col = D3DCOLOR_RGBA(255, 255, 255, Spritebox.Fade);
	Spritebox.vertex_2d[2].col = D3DCOLOR_RGBA(255, 255, 255, Spritebox.Fade);
	Spritebox.vertex_2d[3].col = D3DCOLOR_RGBA(255, 255, 255, Spritebox.Fade);

	//テクスチャ座標の設定
	Spritebox.vertex_2d[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Spritebox.vertex_2d[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Spritebox.vertex_2d[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Spritebox.vertex_2d[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	
	Spritebox.Createflag = true;

	return S_OK;

}

void CSprite::SetFade(int nowfade)
{
	Spritebox.Fade = nowfade;

	Spritebox.vertex_2d[0].col = D3DCOLOR_RGBA(255, 255, 255, Spritebox.Fade);
	Spritebox.vertex_2d[1].col = D3DCOLOR_RGBA(255, 255, 255, Spritebox.Fade);
	Spritebox.vertex_2d[2].col = D3DCOLOR_RGBA(255, 255, 255, Spritebox.Fade);
	Spritebox.vertex_2d[3].col = D3DCOLOR_RGBA(255, 255, 255, Spritebox.Fade);

}