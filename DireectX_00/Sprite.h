#pragma once

#include"ObjManager.h"
#include "Window.h"

typedef struct{
	D3DXVECTOR3 pos;	//���_����
	float rhw;			//�e�N�X�`���摜
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`���摜/����
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

