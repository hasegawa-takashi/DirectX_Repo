#pragma once
#include "ObjManager.h"
#include"MeshRender.h"

class CField :public ObjBase
{
public:
	CField();
	~CField();
	//----------------------------
	// --- オブジェクトの初期化
	void Init();
	//----------------------------
	// --- オブジェクトの更新
	void Update();
	//----------------------------
	// --- オブジェクトの更新(あとから用)c
	void LateUpdate(){};
	//----------------------------
	// --- オブジェクトの描画
	void Draw();
	//----------------------------------------
	// --- オブジェクトの描画(あとから用)
	void LateDraw(){};
	//----------------------------------------
	// --- オブジェクトの描画(あとから用)
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
	// --- コリジョンの設定
	ColBox GetCol(){ return Collision; }
	
private:
	bool	m_bLoad;
	ColBox Collision;

};

