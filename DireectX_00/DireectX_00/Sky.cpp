// スカイドーム クラス実装

#include "Sky.h"
#include "Camera.h"

// 定数
#define PATH_MESHSKY	_T("../data/model/sky.x")

// コンストラクタ
CSky::CSky()
{

}

// デストラクタ
CSky::~CSky(void)
{
}

// 初期化
void CSky::Init()
{
	m_ModelMesh.Initialize(PATH_MESHSKY);
	// カメラオブジェクトの取得
	CObjManager::Instance()->SerchObj(ID_CAMERA, CameraObj);

	CObjManager::Instance()->LateRenderPush(this);

}

// 更新
void CSky::Update()
{
}

// 更新後処理
void CSky::LateUpdate()
{
	D3DXVECTOR3 pos;
	pos = CameraObj.begin()->second->GetPos();
	
	D3DXMATRIX world;
	D3DXMatrixTranslation(&world, pos.x, pos.y, pos.z);

	m_mtxWorld = world;

	m_ModelMesh.Update(m_mtxWorld);

}

// 描画
void CSky::Draw()
{
	// 何もしない
}

// 半透明描画
void CSky::LateDraw()
{
	LPDIRECT3DDEVICE9 pD = CWindow::Instance()->GetDevice();
	pD->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_ModelMesh.Render();
	pD->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pD->SetRenderState(D3DRS_LIGHTING, TRUE);

}

// 解放
void CSky::Release()
{
	m_ModelMesh.Finalize();
}