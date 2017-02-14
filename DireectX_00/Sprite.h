#pragma once

#include"ObjManager.h"
#include "Window.h"

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

class CSprite
{
private:

public:
	CSprite();
	~CSprite();

	void Init();
	void Update();
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

