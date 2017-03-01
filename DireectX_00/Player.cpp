#include"Player.h"
#include"Input.h"
#include"RenderMgr.h"
#include"Scene.h"
#include"Calculation.h"

// 定数宣言
#define DEFINE_VEC3 D3DXVECTOR3(0,0,0)
#define ROLLSPEED (0.001f)

#define PATH_MESHPLAYER	_T("../data/model/Player.x")
#define PATH_PARTICLE_1	_T("../data/Texture/Spark.png")

////////////////////////////////////////////////////////////////////////
//
//		コンストラクタ
//
////////////////////////////////////////////////////////////////////////
Player::Player()
{

	// 変数初期化
	m_Pos = D3DXVECTOR3(0, 0, 0);
	m_Dir = 0.0f;
	//m_CameraMove = DEFINE_VEC3;
	m_Speed = 0.3f;
	m_Dash = 0.2f;
	m_Step = 1.0;

	m_Jump = false;
	m_Move = false;
	m_dAnimTime = 0.0;
	HitCnt = false;
	BalletCnt = 0;

	m_ModelMesh = new CMeshRender;

	if (!m_Load)
	{
		m_Load = m_ModelMesh->Initialize(PATH_MESHPLAYER);

		if (m_Load)
		{
			m_ModelMesh->SwitchAnimSet(1);
		}
	}

	D3DXMatrixIdentity(&m_mtxWorld);

	m_mtxWorld._41 = m_Pos.x;
	m_mtxWorld._42 = m_Pos.y;
	m_mtxWorld._43 = m_Pos.z;

	Collision.m_Pos = m_Pos + D3DXVECTOR3(0, 1.0f, 0);

	Collision.m_fLength[0] = 0.5f;
	Collision.m_fLength[1] = 1.5f;
	Collision.m_fLength[2] = 0.3f;

	// 弾の初期化
	CBallet Ballet;
	// 弾数だけかくほ～
	for (size_t i = 0; i < MAX_BALLET; i++)
	{
		_vecbullet_L.push_back(Ballet);
	}
	
}

////////////////////////////////////////////////////////////////////////
//
//		デストラクタ
//
////////////////////////////////////////////////////////////////////////
Player::~Player()
{
}

////////////////////////////////////////////////////////////////////////
//
//		プレイヤー初期化
//
////////////////////////////////////////////////////////////////////////
void Player::Init()
{
	// プレイヤーのなまえずけ　
	ObjNumb = CObjManager::Instance()->RenameObj(ID_PLAYER,ObjID);

	// カメラオブジェクトの取得。
	// 型キャストにて無理やり変換をかけている。
	// あまりいい方法ではないと思うのであまりやらないように注意するべき( ﾟДﾟ)
	CObjManager::Instance()->SerchObj(ID_CAMERA, CameraObjMgr);
	ObjBase* hoge = CameraObjMgr.begin()->second;
	CameraObj = dynamic_cast<CCamera*>(hoge);
	
	// 弾の初期化
	for (auto itr = _vecbullet_L.begin(); itr != _vecbullet_L.end(); ++itr )
	{
		itr->Init();
	}


	CObjManager::Instance()->LateRenderPush(this);
}

////////////////////////////////////////////////////////////////////////
//
//		プレイヤーの更新処理
//
////////////////////////////////////////////////////////////////////////
void Player::Update()
{
	// 移動更新
	Move();
	
	// 射撃入力射撃
	Shot();

	// 向きの更新
	ChangeTPSDir();

	// キャラの移動
	m_Pos.x = m_mtxWorld._41 -= (m_mtxWorld.m[2][0] * m_MoveSpeed.z);
	m_Pos.y = m_mtxWorld._42 -= (m_mtxWorld.m[2][1] * m_MoveSpeed.z);
	m_Pos.z = m_mtxWorld._43 -= (m_mtxWorld.m[2][2] * m_MoveSpeed.z);
	
	// 床との移動判定
	CheckFloor();
	
	// アニメーションメッシュの更新
	m_ModelMesh->Update(m_mtxWorld);
	
	// 弾の更新
	for (auto itr = _vecbullet_L.begin(); itr != _vecbullet_L.end(); ++itr)
	{
		itr->Update();
	}

	// こんなもの！
	Reset();

}

////////////////////////////////////////////////////////////////////////
//
//		プレイヤーの描画
//
////////////////////////////////////////////////////////////////////////
void Player::Draw()
{

	//D3DXMatrixRotationYawPitchRoll();

	// キャラクターの描画
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_SPECULARENABLE, FALSE);	// 鏡面反射を無効
	m_ModelMesh->Render();
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	// 弾の描画
	for (auto itr = _vecbullet_L.begin(); itr != _vecbullet_L.end(); ++itr)
	{
		if (itr->GetShotFlag())
			continue;
		itr->LateDraw();
	}

}

void Player::LateDraw(){}
void Player::UIDraw(){}

////////////////////////////////////////////////////////////////////////
//
//	プレイヤーの終了処理	
//
////////////////////////////////////////////////////////////////////////
void Player::Release()
{
	// メッシュの終了処理
	if (m_Load)
	{
		m_ModelMesh->Finalize();
		delete m_ModelMesh;
		m_Load = false;
	}

	// 弾の終了処理
	if (!_vecbullet_L.empty())
	{
		_vecbullet_L.clear();
	}
}

////////////////////////////////////////////////////////////////////////
//		
//	移動入力
//
////////////////////////////////////////////////////////////////////////
void Player::Move()
{

	float MoveSpeed = 0;	// 移動量

	// ダッシュ処理
	if (CInput::GetKeyPress(DIK_LSHIFT))
	{
		MoveSpeed += m_Dash;
	}

	if (CInput::GetKeyTrigger(DIK_SPACE))
	{
		MoveSpeed += m_Step;
	}

	// 移動処理
	if (CInput::GetKeyPress(DIK_RIGHT) || CInput::GetKeyPress(DIK_D) ||
		CInput::GetKeyPress(DIK_LEFT) || CInput::GetKeyPress(DIK_A) ||
		CInput::GetKeyPress(DIK_UP) || CInput::GetKeyPress(DIK_W) ||
		CInput::GetKeyPress(DIK_DOWN) || CInput::GetKeyPress(DIK_S))
	{
		// 移動方向
		if (CInput::GetKeyPress(DIK_RIGHT) || CInput::GetKeyPress(DIK_D))
		{
			m_Dir = 90.0f;
		}
		if (CInput::GetKeyPress(DIK_LEFT) || CInput::GetKeyPress(DIK_A)) {
			m_Dir = -90.0f;
		}
		if (CInput::GetKeyPress(DIK_UP) || CInput::GetKeyPress(DIK_W)) {
			m_Dir = 0.0f;
		}
		if (CInput::GetKeyPress(DIK_DOWN) || CInput::GetKeyPress(DIK_S)) {
			m_Dir = 180.0f;
		}

		if ( (CInput::GetKeyPress(DIK_RIGHT) || CInput::GetKeyPress(DIK_D)) &&
			(CInput::GetKeyPress(DIK_UP) || CInput::GetKeyPress(DIK_W)) )
		{
			m_Dir = 45.0f;
		}

		if ((CInput::GetKeyPress(DIK_RIGHT) || CInput::GetKeyPress(DIK_D)) &&
			(CInput::GetKeyPress(DIK_DOWN) || CInput::GetKeyPress(DIK_S))) {
			m_Dir = 135.0f;
		}

		if ((CInput::GetKeyPress(DIK_LEFT) || CInput::GetKeyPress(DIK_A)) &&
			(CInput::GetKeyPress(DIK_DOWN) || CInput::GetKeyPress(DIK_S))) {
			m_Dir = 225.0f;
		}

		if ((CInput::GetKeyPress(DIK_LEFT) || CInput::GetKeyPress(DIK_A)) &&
			(CInput::GetKeyPress(DIK_UP) || CInput::GetKeyPress(DIK_W)) ) {
			m_Dir = -45.0f;
		}

		m_MoveSpeed.z += (m_Speed + MoveSpeed);
		m_Move = true;

	}
	else{
		m_Move = false;
	}

	

}

////////////////////////////////////////////////////////////////////////
//		
//	ボーンの回転
//
////////////////////////////////////////////////////////////////////////
void Player::TransBorn()
{
	D3DXMATRIX* HipBorn = m_ModelMesh->SerchBorn("root_spine_02");


	D3DXMATRIX rot;
	D3DXVECTOR3 YVec = D3DXVECTOR3(HipBorn->_21, HipBorn->_22, HipBorn->_23);
	D3DXVECTOR3 XVec = D3DXVECTOR3(HipBorn->_11, HipBorn->_12, HipBorn->_13);
	D3DXVECTOR3 ZVec = D3DXVECTOR3(HipBorn->_31, HipBorn->_32, HipBorn->_33);


	D3DXMatrixRotationZ(&rot, D3DXToRadian(0));
	D3DXVec3TransformCoord(&XVec, &XVec, &rot);

	D3DXVec3Cross(&ZVec, &XVec, &YVec);
	D3DXVec3Normalize(&ZVec, &ZVec);
	D3DXVec3Cross(&XVec, &YVec, &ZVec);
	D3DXVec3Normalize(&XVec, &XVec);

	XVec *= 0.01f;
	ZVec *= 0.01f;

	memcpy(HipBorn->m[0], &XVec, sizeof(D3DXVECTOR3));
	memcpy(HipBorn->m[2], &-ZVec, sizeof(D3DXVECTOR3));

}

////////////////////////////////////////////////////////////////////////
//		
//	射撃入力(左武器の処理)
//
////////////////////////////////////////////////////////////////////////
void Player::Shot()
{
	// 弾を撃つ
	if (CInput::GetMousePress(0))
	{
		for (auto itr = _vecbullet_L.begin(); itr != _vecbullet_L.end(); ++itr)
		{
			if (!itr->GetShotFlag())
				continue;
			itr->CreateBallet(balletpram_L);

		}
	}

	if (CInput::GetKeyPress(DIK_E)) {

		for (auto itr = _vecbullet_L.begin(); itr != _vecbullet_L.end(); ++itr)
		{
			BalletCnt = 0;

			itr->Reload();
		}

	}
}

////////////////////////////////////////////////////////////////////////
//		
//	タゲ破壊数による目的の以降
//	これどっかに移植するべき
//
////////////////////////////////////////////////////////////////////////
void Player::LastRun()
{
	/*if (HitCnt < MAX_BOT)
	{
		for (size_t i = 0; i < MAX_BALLET; i++)
		{
			if (Ballet[i].GetHitCheck())
				HitCnt++;
		}
	}
	else if (CObjManager::Instance()->CollisonCheck(ID_GOAL, COL_OBB, Collision))
	{

		CSceneMgr::Instance()->ChangeScene(new CEnd);
	}
	
	if (m_Pos.y < -10)
	{

		CSceneMgr::Instance()->ChangeScene(new CEnd);
	}*/
}

////////////////////////////////////////////////////////////////////////
//		
//	プレイヤーの向きを変える更新処理
//	ACT用
////////////////////////////////////////////////////////////////////////
void Player::ChangeACTDir()
{
	if (m_Move)
	{
		if (m_Load)
		{
			m_ModelMesh->SwitchAnimSet(0);
		}

		// プレイヤーの向きの設定
		D3DXMATRIX rot;
		D3DXVECTOR3 View;

		View = (m_Pos - CameraObj->GetPos());

		D3DXMatrixRotationY(&rot, D3DXToRadian(m_Dir));
		D3DXVec3TransformCoord(&View, &View, &rot);

		D3DXVECTOR3 ZVec = View;
		D3DXVECTOR3 YVec = m_mtxWorld.m[1];
		D3DXVECTOR3 XVec;

		D3DXVec3Cross(&XVec, &ZVec, &YVec);
		D3DXVec3Normalize(&XVec, &XVec);
		D3DXVec3Cross(&ZVec, &YVec, &XVec);
		D3DXVec3Normalize(&ZVec, &ZVec);

		memcpy(m_mtxWorld.m[0], &XVec, sizeof(D3DXVECTOR3));
		memcpy(m_mtxWorld.m[2], &-ZVec, sizeof(D3DXVECTOR3));

		// 壁の判定
		Collision.m_Pos.x = (m_Pos.x + 0.0f);
		Collision.m_Pos.y = (m_Pos.y + 1.0f);
		Collision.m_Pos.z = (m_Pos.z + 0.0f);

		Collision.Ray = ZVec;

		m_NowDir = ZVec;

		if (CObjManager::Instance()->CollisonCheck(ID_FIELD, COL_RAY, Collision))
		{
			D3DXVECTOR3 in = Collision.m_Pos - Collision.ResultPos;
			FLOAT out = D3DXVec3Length(&in);
			if (out < 0.5f)
			{
				m_Pos.z = m_mtxWorld._43 = Collision.ResultPos.z;
				m_MoveSpeed = DEFINE_VEC3;
			}
		}

	}
	else{
		if (m_Load)
		{
			m_ModelMesh->SwitchAnimSet(1);
		}
	}

}

////////////////////////////////////////////////////////////////////////
//		
//	プレイヤーの向きを変える更新処理
//	TPS用
////////////////////////////////////////////////////////////////////////
void Player::ChangeTPSDir()
{
	D3DXMATRIX dir = CameraObj->GetZVec();

	

}

////////////////////////////////////////////////////////////////////////
//		
//	床とのあたり判定を取る処理
//
////////////////////////////////////////////////////////////////////////
void Player::CheckFloor()
{
	// 床の設定
	Collision.m_Pos.x = (m_Pos.x + 0.0f);
	Collision.m_Pos.y = (m_Pos.y + 3.0f);
	Collision.m_Pos.z = (m_Pos.z + 0.0f);

	Collision.Ray.x = 0.0f;
	Collision.Ray.y = -1.0f;
	Collision.Ray.z = 0.0f;

	if (CObjManager::Instance()->CollisonCheck(ID_FIELD, COL_RAY, Collision))
	{
		m_Pos.y = m_mtxWorld._42 = Collision.ResultPos.y;
	}
	else{
		m_mtxWorld._42 -= 0.1f;
	}
}

////////////////////////////////////////////////////////////////////////
//		
//	変数リセット
//
////////////////////////////////////////////////////////////////////////
void Player::Reset()
{
	// 差分の初期化
	m_MoveSpeed = DEFINE_VEC3;
	Collision.WorldMtx = m_mtxWorld;
}