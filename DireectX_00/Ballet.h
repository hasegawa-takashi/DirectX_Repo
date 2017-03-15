#pragma once

#include"Window.h"
#include"ObjManager.h"
#include"MeshRender.h"
#include"Billbord.h"


struct BulletBox
{
	float fSpeed;			// 弾の速度
	D3DXVECTOR3 Dir;		// 弾の向き
	D3DXVECTOR3 Pos;		// 弾のポジション
	float Length;			// 弾の発射距離
	float SwingRange;		// エイムのブレ幅
	int BalletType;			// 弾の種類
};

enum Ballet_Type{

	MAX_BULLET_TYPE
};

class CBallet : public ObjBase
{
public:
	CBallet();
	~CBallet();

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
	void LateDraw(){};
	void UIDraw(){};
	//----------------------------
	// --- オブジェクトの削除
	void Release();
	//----------------------------
	// --- ポーズ画面
	void Pause(){};
	//----------------------------
	// --- 最終処理全削除用
	bool AllRelaseObj(){ return true; };


	//----------------------------------------
	// --- Reload
	void Reload(){ ShotFlag = false; }

	bool GetShotFlag(){ return ShotFlag; }

	bool GetHitCheck();

	//----------------------------------------
	// --- 弾の生成
	// --- 弾の情報を持った構造体を入れて、どうぞ
	bool CreateBallet(BulletBox bullet);

private:
	

	float m_Range;				// 弾の最大距離
	D3DXVECTOR3 m_Dir;			// 弾の向き
	bool ShotFlag;				// 弾を撃った?(Y/N)

	float m_MaxError;			// ブレの範囲

	bool m_Load;				// モデル読み込みフラグ
	
	bool Hitflag;

};

