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
	m_ModelMesh = new CMeshRender;
	m_ModelMesh->Initialize(PATH_MESHSKY);
	
	// カメラオブジェクトの取得
	CameraObj = GetObjMgr()->SerchObj(ID_CAMERA);

}

// 更新
void CSky::Update()
{
}

// 更新後処理
void CSky::LateUpdate()
{
	D3DXVECTOR3 pos;

	for (auto& p : CameraObj)
	{
		pos = p->GetPos();
	}

	D3DXMATRIX world;
	D3DXMatrixTranslation(&world, pos.x, pos.y, pos.z);

	m_mtxWorld = world;

	m_ModelMesh->Update(m_mtxWorld);

}

// 描画
void CSky::Draw()
{
	// 何もしない
	LPDIRECT3DDEVICE9 pD = GetDxMgr()->GetDxDevice();
	pD->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_ModelMesh->Render();
	pD->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pD->SetRenderState(D3DRS_LIGHTING, TRUE);

}

// 半透明描画
void CSky::LateDraw()
{
	

}

// 解放
void CSky::Release()
{
	//m_ModelMesh->Finalize();
	delete m_ModelMesh;
}