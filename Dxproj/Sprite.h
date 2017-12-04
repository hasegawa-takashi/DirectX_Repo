#pragma once

#include"includeheader.h"


#define	NUM_VERTEX		(4)		// 頂点数
#define	NUM_POLYGON		(2)		// ポリゴン数

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )



typedef struct{
	D3DXVECTOR3 pos;	//頂点左上
	float rhw;			//テクスチャ画像
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ画像/左上
}VERTEX_2D;

struct SpriteBox
{
	LPDIRECT3DTEXTURE9 m_Texture;
	LPD3DXSPRITE m_Sprite;
	VERTEX_2D vertex_2d[NUM_VERTEX];
	int Fade;
	bool Createflag;
};

//////////////////////////////////////////////////////////////
//
//		平面描画用クラス
//
/////////////////////////////////////////////////////////////
class CSprite
{
private:

public:
	CSprite();
	~CSprite();

	void Render();
	void Release();

	void SetFade(int nowfade);

	HRESULT CreateMakeVertex2DPolygon(
		LPCTSTR TexFile,
		float nX,
		float nY,
		float Width,
		float Height,
		int fade);

	SpriteBox Spritebox;

};

