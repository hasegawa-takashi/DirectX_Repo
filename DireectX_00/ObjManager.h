#pragma once

// インクルード
#include<list>
#include<map>
#include<string>
#include<vector>

#include"MeshRender.h"

// グローバル

// クラス定義

enum ObjName
{
	ID_PLAYER = 0,	// プレイヤー用の番号
	ID_ENEMY,		// エネミー用の番号
	ID_FIELD,		// フィールド用の番号
	ID_BALLET,		// バレット用の番号
	ID_CAMERA,		// カメラ用
	ID_GOAL,		// ゴール用
	ID_OTHER,		// その他の番号
	MAX_ID
};

enum CollisionType
{
	COL_SPHERE,		// 球::球
	COL_AABB,		// AABB::AABB
	COL_OBB,		// OBB::OBB
	COL_RAY,		// RAY::MESH
	COL_RAY_SPHERE,	// RAY::球
	COL_RAY_OBB,	// RAY::OBB
	MAX_COL
};

//////////////////////////////////////////////////////////////
//
//		ColBox
//			検索の関係上ここに描く。
//			当たり判定を持たせるオブジェクトには保持させること
//
/////////////////////////////////////////////////////////////
class ColBox{

public:
	// OBB判定
	D3DXVECTOR3 m_Pos;              // 位置
	D3DXVECTOR3 m_NormaDirect[3];   // 方向ベクトル
	FLOAT m_fLength[3];             // 各軸方向の長さ
	float Radius;					// 半径
	D3DXMATRIX WorldMtx;			// ワールドマトリクスs
	D3DXVECTOR3 Ray;				// レイの方向
	D3DXVECTOR3 ResultPos;			// 交差地点の結果を取得
	int m_SetObjId;					// 対象のメッシュ
	int IdentNumb;					// 固有ナンバー

	std::multimap<int, int> Obj;	// オブジェクトの固有番号

};


//////////////////////////////////////////////////////////////
//
//		objectbase
//			がばがばだけどゲーム内オブジェクト用の管理クラス
//
/////////////////////////////////////////////////////////////
class ObjBase
{
public:
	ObjBase(){}
	virtual ~ObjBase(){}

	// === 継承するメッセージ === //

	// それぞれの更新処理のため必須
	virtual void Init() {};
	virtual void Update() {};
	virtual void LateUpdate() {};
	virtual void Draw() {};
	virtual void LateDraw() {};
	virtual void UIDraw() {};
	virtual void Release() {};
	virtual void Pause() {};
	virtual bool AllRelaseObj() { return true; }

	// 複数ある可能性があるもの
	virtual ColBox GetCol() = 0;

	// 一つの固有であるもの
	virtual CMeshRender* GetRender(){ return m_ModelMesh; }
	virtual void SetidentNumb(int ID){ ObjNumb = ID; }
	virtual int GetidentNumb(){ return ObjNumb; }
	virtual void SetPos(D3DXVECTOR3 pos){ m_Pos = pos; }
	virtual D3DXVECTOR3 GetPos(){ return m_Pos; }

protected:

	// === 継承用メッセージ === //

	D3DXMATRIX m_mtxWorld;		// ワールド行列
	CMeshRender *m_ModelMesh;	// モデル描画用
	int ObjNumb;				// モデルの固有番号
	D3DXVECTOR3 m_Pos;			// ポジション

};

typedef std::multimap< int, ObjBase* > OBJMGR;
typedef std::vector<std::pair<float, ObjBase*> > RenderSort;
//////////////////////////////////////////////////////////////
//
//		objectmanager
//			がばがばだけどゲーム内オブジェクト用の管理クラス
//
/////////////////////////////////////////////////////////////
class CObjManager
{
public:
	//----------------------------
	// デストラクタ
	~CObjManager();

	//---------------------------------------
	// オブジェクトマネージャーのインスタンス
	static CObjManager* Instance(void) {
		static CObjManager _instance;
		return &_instance;
	}

	//----------------------------
	// --- オブジェクトの初期化
	void Init();
	//----------------------------
	// --- オブジェクトの更新
	void Update();
	//----------------------------
	// --- オブジェクトの更新
	void LateUpdate();
	//----------------------------
	// --- オブジェクトの描画
	void Draw();
	//----------------------------
	// --- オブジェクトの描画
	void LateDraw();
	//----------------------------
	// --- UIの描画
	void UIDraw();
	//----------------------------
	// --- オブジェクトの削除
	void Release();
	//----------------------------
	// --- オブジェクトの全削除
	bool AllRelaseObj();
	

	// === ここまでオブジェクト処理 === //

	// === ここからオブジェクト管理処理 === //
	// === 選択削除がないことに気付いたこの頃 === //

	//----------------------------
	// --- オブジェクトの挿入
	bool PushObj(ObjBase* obj, UINT ID);

	//----------------------------
	// --- オブジェクトの削除
	bool PopObj(int Numb , int ID);

	//----------------------------
	// --- オブジェクトの交換
	bool ChangeObj(int Numb, ObjBase*);

	//---------------------------
	// --- オブジェクトへの命名
	// --- 色々あっていらない可能性が出てきた
	int RenameObj(UINT ID);
	
	//---------------------------
	// --- オブジェクトの捜索
	void SerchObj(UINT ID, OBJMGR& obj);
	
	//--------------------------------
	// --- どうしようもない物の初期化
	void MonSter(){ Numb = 0;  }

	// === ここから継承の変数宣言 === //
	CMeshRender *m_ModelMesh;	// 描画用の変数クラス

	// === ここから先当たり判定関係 === //
	// === 上手い作り方がわからなかったのでここで一括で当たり判定を構成 === //

	//--------------------------------------
	// --- オブジェクトの検索用+判定も
	// --- 第一引数 :: 探すオブジェクトのID
	// --- 第二引数 :: 検索の方法
	bool CollisonCheck(UINT ID, int Colltype,ColBox &obb1);
	float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0);

	//---------------------------
	// --- OBBの引っ張ってくる設定
	ColBox GetCol() {};

	// === ここから先描画系 === //
	CMeshRender* GetRender() {};

	// === 描画補助用 === //
	// --- 半透明Objのリスト
	bool LateRenderPush(ObjBase* render);

private:

	//----------------------------
	// --- 球体判定
	bool CollisionBSphere(ColBox &obb1, ColBox &obb2);

	//----------------------------
	// --- AABB判定
	bool CollisionAABB(ObjBase* pObj, UINT ID);

	//----------------------------
	// --- OBB判定
	bool CollisionOBB(ColBox &obb1, ColBox &obb2);

	//----------------------------
	// --- Ray+Spher
	bool calcRaySphere(ColBox &obb1, ColBox &obb2);

	//----------------------------
	// --- カメラとの距離を出す
	float CameraDistance(D3DXVECTOR3 SetPos);

private:
	std::list< OBJMGR > ObjList;			// オブジェクトのlist構造
	RenderSort TranslucentObj;		// 半透明Objをまとめてるlist

	int Numb;
};

//=============================================================================
// デバイス呼び出し用
//=============================================================================
inline CObjManager* GetObjMgr()
{
	return CObjManager::Instance();
}


//====================================================================================
//									EOF
//====================================================================================
