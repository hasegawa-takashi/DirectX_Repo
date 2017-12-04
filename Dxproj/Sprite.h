#pragma once

#include"includeheader.h"


#define	NUM_VERTEX		(4)		// ���_��
#define	NUM_POLYGON		(2)		// �|���S����

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )



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

//////////////////////////////////////////////////////////////
//
//		���ʕ`��p�N���X
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

