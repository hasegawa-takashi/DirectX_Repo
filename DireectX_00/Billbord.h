#pragma once
#include "RenderMgr.h"


typedef struct
{
	D3DXVECTOR3 vtx;	//���_���W
	D3DXVECTOR3 normal;	//�@���x�N�g��
	D3DCOLOR    diffuse;	//���ˌ�
	D3DXVECTOR2 tex;	//�e�N�X�`�����W

} VERTEX_3D;


typedef struct{
	VERTEX_3D *vertex3d;
	LPDIRECT3DTEXTURE9		g_pD3DTextureBillboard;
	LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBillboard;
	D3DXMATRIX				g_mtxWorldBillboard;
	int nNumVertex;
	D3DXVECTOR2 Size;
	D3DXVECTOR4 TexPos;
	D3DXVECTOR3 Pos;


}BillbordPlate;


class CBillbord 
{
public:
	CBillbord();
	~CBillbord();

	void Init();
	void Update(D3DXMATRIX World);
	void Render();
	void Release(BillbordPlate *billbord);

	HRESULT CreateMake3DBillbord( LPCTSTR  TexFile,
		float SizeX,
		float SizeY,
		float TexPosLeft,
		float TexPosRight,
		float TexPosUp,
		float TexPosDown);

	BillbordPlate billbox;	//�r���{�[�h���i�[�p

};

