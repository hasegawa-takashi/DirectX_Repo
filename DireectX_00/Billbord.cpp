#include "Billbord.h"
#include"Camera.h"

CBillbord::CBillbord()
{}
CBillbord::~CBillbord()
{}
void CBillbord::Init()
{}

void CBillbord::Update(D3DXMATRIX World)
{
	// ワールド行列から座標の抜き出し + 設定
	billbox.Pos.x = World._41;
	billbox.Pos.y = World._42;
	billbox.Pos.z = World._43;
}

void CBillbord::Release(BillbordPlate *billbord)
{

	if (billbord->g_pD3DTextureBillboard != NULL)
	{// テクスチャの開放
		billbord->g_pD3DTextureBillboard->Release();
		billbord->g_pD3DTextureBillboard = NULL;
	}

	if (billbord->g_pD3DVtxBuffBillboard != NULL)
	{// 頂点バッファの開放
		billbord->g_pD3DVtxBuffBillboard->Release();
		billbord->g_pD3DVtxBuffBillboard = NULL;
	}
	
}

void CBillbord::Render()
{
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	GetDxMgr()->GetDxDevice()->GetTransform(D3DTS_VIEW,&mtxView);

	// ライティングを無効にする
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&billbox.g_mtxWorldBillboard);

	

	// ポリゴンを正面に向ける
#if 0
	// 逆行列を求める
	D3DXMatrixInverse(&g_mtxWorldBillboard[nNumb], NULL, &mtxView);
	g_mtxWorldBillboard[nNumb]._41 = 0.0f;
	g_mtxWorldBillboard[nNumb]._42 = 0.0f;
	g_mtxWorldBillboard[nNumb]._43 = 0.0f;
	//平行移動成分をなくす

#else
	// 転置行列を求める
	billbox.g_mtxWorldBillboard._11 = mtxView._11;
	billbox.g_mtxWorldBillboard._12 = mtxView._21;
	billbox.g_mtxWorldBillboard._13 = mtxView._31;

	billbox.g_mtxWorldBillboard._21 = 0.0f;
	billbox.g_mtxWorldBillboard._22 = 1.0f;
	billbox.g_mtxWorldBillboard._23 = 0.0f;

	billbox.g_mtxWorldBillboard._31 = mtxView._13;
	billbox.g_mtxWorldBillboard._32 = mtxView._23;
	billbox.g_mtxWorldBillboard._33 = mtxView._33;

#endif

	// スケールを反映
	D3DXMatrixScaling(&mtxScale, billbox.Size.x, billbox.Size.y, 1.0f);
	D3DXMatrixMultiply(&billbox.g_mtxWorldBillboard, &billbox.g_mtxWorldBillboard, &mtxScale);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, billbox.Pos.x, billbox.Pos.y, billbox.Pos.z);
	D3DXMatrixMultiply(&billbox.g_mtxWorldBillboard, &billbox.g_mtxWorldBillboard, &mtxTranslate);

	// ワールドマトリックスの設定
	GetDxMgr()->GetDxDevice()->SetTransform(D3DTS_WORLD, &billbox.g_mtxWorldBillboard);

	// 頂点バッファをデバイスのデータストリームにバインド
	GetDxMgr()->GetDxDevice()->SetStreamSource(0, billbox.g_pD3DVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	GetDxMgr()->GetDxDevice()->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	GetDxMgr()->GetDxDevice()->SetTexture(0, billbox.g_pD3DTextureBillboard);

	// ポリゴンの描画
	GetDxMgr()->GetDxDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ラインティングを有効にする
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
}

HRESULT CBillbord::CreateMake3DBillbord(
	LPCTSTR  TexFile,
	float SizeX,
	float SizeY,
	float TexPosLeft,
	float TexPosRight,
	float TexPosUp,
	float TexPosDown)
{
	D3DXCreateTextureFromFile(GetDxMgr()->GetDxDevice(),						// デバイスへのポインタ
		TexFile,			// ファイルの名前
		&billbox.g_pD3DTextureBillboard);	// 読み込むメモリ

	if (FAILED(GetDxMgr()->GetDxDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
		FVF_VERTEX_3D,						// 使用する頂点フォーマット
		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
		&billbox.g_pD3DVtxBuffBillboard,	// 頂点バッファインターフェースへのポインタ
		NULL)))								// NULLに設定
	{
		return E_FAIL;
	}

	 {//頂点バッファの中身を埋める

		 // 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		 billbox.g_pD3DVtxBuffBillboard->Lock(0, 0, (void**)&billbox.vertex3d, 0);

		 // 頂点座標の設定
		 billbox.vertex3d[0].vtx = D3DXVECTOR3(-SizeX / 2, -SizeY / 2, 0.0f);
		 billbox.vertex3d[1].vtx = D3DXVECTOR3(-SizeX / 2, SizeY / 2, 0.0f);
		 billbox.vertex3d[2].vtx = D3DXVECTOR3(SizeX / 2, -SizeY / 2, 0.0f);
		 billbox.vertex3d[3].vtx = D3DXVECTOR3(SizeX / 2, SizeY / 2, 0.0f);

		 billbox.Size.x = SizeX;
		 billbox.Size.y = SizeY;

		 // 法線の設定
		 billbox.vertex3d[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		 billbox.vertex3d[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		 billbox.vertex3d[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		 billbox.vertex3d[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		 // 反射光の設定
		 billbox.vertex3d[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		 billbox.vertex3d[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		 billbox.vertex3d[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		 billbox.vertex3d[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		 // テクスチャ座標の設定
		 billbox.vertex3d[0].tex = D3DXVECTOR2(TexPosLeft, TexPosUp);
		 billbox.vertex3d[1].tex = D3DXVECTOR2(TexPosRight, TexPosUp);
		 billbox.vertex3d[2].tex = D3DXVECTOR2(TexPosLeft, TexPosDown);
		 billbox.vertex3d[3].tex = D3DXVECTOR2(TexPosRight, TexPosDown);

		 // 頂点データをアンロックする
		 billbox.g_pD3DVtxBuffBillboard->Unlock();
	 }

	 return S_OK;

}