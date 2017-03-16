#pragma once

// インクルード
#include<list>
#include<map>
#include<string>
#include<vector>
#include<memory>
#include<array>
#include"MeshRender.h"
#include"Collision.h"

// 
using namespace std;

// IDの種類
enum ObjName
{
	ID_PLAYER = 0,	// プレイヤー用の番号
	ID_ENEMY,		// エネミー用の番号
	ID_FIELD,		// フィールド用の番号
	ID_BALLET,		// バレット用の番号
	ID_CAMERA,		// カメラ用
	ID_GOAL,		// ゴール用
	ID_OTHER,		// その他の番号
	ID_FADE,		// Fade用オブジェクト
	MAX_ID
};

/*
OBJMGRの構造
-------	 -------
|  ID   |	|       |
|	+   |---|OBJBase|・・・・・・・・
|OBJBase|	|       |
-------	 -------
|
-------	 -------
|  ID   |	|       |
|	+   |---|OBJBase|・・・・・・・・
|OBJBase|	|       |
-------	 -------
*/

//////////////////////////////////////////////////////////////
//
//		ObjBase
//			がばがばだけどゲーム内オブジェクト用の管理クラス
//
/////////////////////////////////////////////////////////////
class ObjBase
{
protected:

	// === 継承用メッセージ === //
	ColBox m_Collision;			// 当たり判定用
	D3DXMATRIX m_mtxWorld;		// ワールド行列
	CMeshRender *m_ModelMesh;	// モデル描画用
	int ObjNumb;				// モデルの固有番号
	ObjName ObjID;				// モデルのID番号
	D3DXVECTOR3 m_Pos;			// ポジション
	bool NonDeleteObj = false;	// 破壊不可Obj

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
	virtual ColBox GetCol() {};

	// 一つの固有であるもの
	virtual CMeshRender* GetRender(){ return m_ModelMesh; }
	virtual void SetidentNumb(int ID){ ObjNumb = ID; }
	virtual int GetidentNumb(){ return ObjNumb; }
	virtual void SetPos(D3DXVECTOR3 pos){ m_Pos = pos; }
	virtual D3DXVECTOR3 GetPos(){ return m_Pos; }
	virtual bool GetNonDestFlag() { return NonDeleteObj; }
	virtual int GetIDNumb() { return (int)ObjID; }

};

//////////////////////////////////////////////////////////////
//
//		ObjList
//			がばがばだけどゲーム内オブジェクト用の管理クラス
//
/////////////////////////////////////////////////////////////
class ObjList
{

public:
	// コンストラクタ
	ObjList() {}

	// デストラクタ
	virtual ~ObjList() {
		for (auto& pObj : m_ObjList)
			delete pObj;
	}

	//======================================
	//
	//	listのGetter
	//
	//======================================
	list<ObjBase*> GetObjlist()
	{
		return m_ObjList;
	}

	//======================================
	//
	//	ObjListへ追加
	//
	//======================================
	void AddObject(ObjBase* pObj)
	{
		m_ObjList.push_back(pObj);
	}


	//======================================
	//
	//	固有IDを探してObjリストから削除
	//
	//
	//======================================
	bool RemoveObject(ObjBase* pObj)
	{
		for (auto p : m_ObjList)
		{
			if (p->GetidentNumb() != pObj->GetidentNumb())
				continue;

			m_ObjList.remove(p);
			delete p;
			return true;

		}

		return false;

	}
	
	bool RemoveObject(int IdentNumb)
	{
		for (auto p : m_ObjList)
		{
			if (p->GetidentNumb() != IdentNumb)
				continue;

			m_ObjList.remove(p);
			delete p;
			return true;

		}

		return false;
	}

	//----------------------------
	// --- オブジェクトの初期化
	void Init() {

		for (auto p : m_ObjList)
		{
			p->Init();
		}

	};

	//----------------------------
	// --- オブジェクトの更新
	void Update() {

		for (auto p : m_ObjList)
		{
			p->Update();
		}

	};

	//----------------------------
	// --- オブジェクトの更新
	void LateUpdate() {

		for (auto p : m_ObjList)
		{
			p->LateUpdate();
		}

	};

	//----------------------------
	// --- オブジェクトの描画
	void Draw() {

		for (auto p : m_ObjList)
		{
			p->Draw();
		}

	};

	//----------------------------
	// --- オブジェクトの描画
	void LateDraw() {

		for (auto p : m_ObjList)
		{
			p->LateDraw();
		}

	};
	
	//----------------------------
	// --- UIの描画
	void UIDraw() {

		for (auto p : m_ObjList)
		{
			p->UIDraw();
		}

	};
	
	//----------------------------
	// --- オブジェクトの削除
	void Release() {

		for (auto p : m_ObjList)
		{
			p->Release();
		}

	};
	
	//----------------------------
	// --- オブジェクトの全削除
	bool AllDeleteObj() {

		for (auto p : m_ObjList)
		{
			p->AllRelaseObj();
			delete p;
		}

		return true;

	};

	//----------------------------
	// --- 破壊フラグの取得
	std::list<ObjBase*> GetExculdeObj() {

		std::list<ObjBase*> GetObj;

		for (auto p : m_ObjList)
		{
			if( p->GetNonDestFlag() )
				GetObj.push_back(p);
		}

		return GetObj;

	};

private:
	list<ObjBase*> m_ObjList;
};

// 後から描画するものの設定
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
	bool ChangeObj(int ID, int IdentNumb, ObjBase*);

	//---------------------------
	// --- オブジェクトへの命名
	// --- 色々あっていらない可能性が出てきた
	int RenameObj(UINT ID, ObjName &SetObj);
	
	//---------------------------
	// --- オブジェクトの捜索
	list<ObjBase*> SerchObj(UINT ID);
	
	//-----------------------------------------------------------
	// --- オブジェクトのポインタをリストから外す
	/* 除外フラグの立っているオブジェクトをListから外し、
		その除外オブジェクトをリストにして返す*/
	std::list<std::list<ObjBase*>>  ExculdeObj();

	//--------------------------------
	// --- どうしようもない物の初期化
	//void MonSter(){ Numb = 0;  }

	// === ここから継承の変数宣言 === //
	CMeshRender *m_ModelMesh;	// 描画用の変数クラス

	// === ここから先描画系 === //
	CMeshRender* GetRender() {};

	// === 描画補助用 === //
	// --- 半透明Objのリスト
	bool LateRenderPush(ObjBase* render);

private:

	//----------------------------
	// コンストラクタ
	CObjManager();

	//----------------------------
	// --- カメラとの距離を出す
	float CameraDistance(D3DXVECTOR3 SetPos);

private:
	RenderSort TranslucentObj;		// 半透明Objをまとめてるlist

	array<ObjList*,MAX_ID> m_ObjListArray;	//

	unsigned int Numb = 10;						// 固有ID用
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
