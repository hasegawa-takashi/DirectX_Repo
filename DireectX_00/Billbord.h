#pragma once
#include "RenderMgr.h"


typedef struct
{
	D3DXVECTOR3 vtx;	//頂点座標
	D3DXVECTOR3 normal;	//法線ベクトル
	D3DCOLOR    diffuse;	//反射光
	D3DXVECTOR2 tex;	//テクスチャ座標

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

	BillbordPlate billbox;	//ビルボード情報格納用

};

