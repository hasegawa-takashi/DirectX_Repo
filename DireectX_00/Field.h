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
	
	
private:
	bool	m_bLoad;
	
	struct BoxGrain
	{
		CMeshRender m_Blocklist;	// Cubeのモデル
		float time;					// 時間
		int power;					// 強さ
	};

	BoxGrain m_boxgrains[10];

};

