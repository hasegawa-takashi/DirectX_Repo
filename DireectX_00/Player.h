#pragma once
#include "ObjManager.h"
#include"MeshRender.h"
#include "Window.h"
#include"Billbord.h"
#include"Ballet.h"
#include<vector>
#include"Camera.h"

#define MAX_BALLET (30)

class Player : public ObjBase
{
public:
	//----------------------------
	// --- コンストラクタ
	Player();
	
	//----------------------------
	// --- デストラクタ
	~Player();

	//----------------------------
	// --- オブジェクトの初期化
	void Init();
	//----------------------------
	// --- オブジェクトの更新
	void Update();
	//----------------------------
	// --- オブジェクトの更新(あとから用)
	void LateUpdate(){};
	//----------------------------
	// --- オブジェクトの描画
	void Draw();
	//----------------------------------------
	// --- オブジェクトの描画(あとから用)
	void LateDraw();
	//----------------------------------------
	// --- オブジェクトの描画(あとから用)
	void UIDraw();
	//----------------------------
	// --- オブジェクトの削除
	void Release();
	//----------------------------
	// --- ポーズ画面
	void Pause(){};
	//----------------------------
	// --- 最終処理全削除用
	bool AllRelaseObj(){ return true; }

	//----------------------------
	// --- 向きの取得
	D3DXVECTOR3 GetDir(){ return m_NowDir; }

	//----------------------------------------
	// --- ゲームクリア
	void LastRun();


private:

	// カメラ用のオブジェク
	CCamera *CameraObj;					// 型キャスト後のオブジェクト
	OBJMGR CameraObjMgr;				// 型キャスト前のオブジェクト


	int HitCnt;
	int BalletCnt;						// 発射バレットの弾数

	float m_Dir;						// 移動向き
	float m_Rotate;						// プレイヤーの向きs
	D3DXVECTOR3 m_NowDir;
	D3DXVECTOR3 m_MoveSpeed;			// 動く速度
	

	float m_Speed;						// 移動速度
	float m_Dash;						// ダッシュ移動速度
	float m_Step;						// ステップスピード(距離ともいう)

	bool m_Jump;						// ジャンプフラグ
	bool m_Move;						// 移動フラグ
	bool m_Load;						// モデル読み込みフラグ

	float m_dwPrev;						// 経過時間計測用
	double m_dAnimTime;					// アニメーション時間

	BulletBox balletpram_L;				// L武器
	BulletBox balletpram_R;				// R武器

	std::vector<CBallet> _vecbullet_L;	// バレットのベクター
	std::vector<CBallet> _vecbullet_R;	// バレットのベクター

	// === ここから先private関数 === //
	void Move();						// 移動用
	void Shot();						// 射撃用
	void TransBorn();					// ボーンの捻じ曲げ
	void ChangeACTDir();				// 向きのきりかえよう
	void ChangeTPSDir();				// 向きのきりかえよう
	void CheckFloor();					// 床との判定処理
	void Reset();
};

