#pragma once

#pragma region ObjBase
#include<d3dx9.h>

// ---------------------------------------
// --- ゲーム内Objに継承するベースクラス
class ObjBase
{
protected:
	int m_ObjNumb;					// 固有ID
	int m_ObjID;					// enum :: ObjName
	bool m_NonDeleteObj = false;	// 破壊不可Obj
	D3DXVECTOR3 m_Position;			// 座標(X,Y,Z)
	D3DXMATRIX m_WorldMtx;			// Objのワールド行列

public:
	ObjBase(){}
	virtual ~ObjBase(){}

	virtual void Init() {}			// 初期化
	virtual void Update() {}		// 更新
	virtual void LateUpdate() {}	// そのまんま
	virtual void Draw() {}			// 描画
	virtual void LateDraw() {}		// そのまんま
	virtual void UIDraw() {}		// UI描画
	virtual void Release() {}		// 削除	
	virtual void Pause() {}			// ポーズ中

	virtual void SetidentNumb(int ID) { m_ObjNumb = ID; }		// 固有番号のセット
	virtual int GetidentNumb() { return m_ObjNumb; }			// 固有番号の取得
	virtual bool GetNonDestFlag() { return m_NonDeleteObj; }	// 破壊しないObjの取得
	virtual int GetObjID() { return m_ObjID; }					// ObjNameの取得
	virtual D3DXVECTOR3 GetPosition() { return m_Position; }	// 座標の取得
};
#pragma endregion

#include"includeheader.h"

// --------------------
// --- IDの種類
enum ObjName
{
	ID_PLAYER = 0,	// プレイヤー用の番号
	ID_OTHER,		// その他の番号
	ID_FADE,		// Fade用オブジェクト
	MAX_ID
};


#pragma region Objlist
// --------------------------------
// --- ゲームオブジェクトを管理するリスト
class ObjList
{
public:

	// --------------------
	// --- コンストラクト
	ObjList(){}

	// --------------------
	// --- デストラクタ
	virtual ~ObjList(){
		if (m_Objlist.empty())
		{
			for (auto& _Obj : m_Objlist)
				delete _Obj;
		}
	}

	// ------------------------------
	// --- List内に入ってるObjの取得
	std::list<ObjBase*> GetObjList()
	{
		return m_Objlist;
	}

	// ------------------------------
	// --- オブジェクトの追加
	void AddObject(ObjBase* _Obj)
	{
		m_Objlist.push_back(_Obj);
	}

	// ------------------------------
	// --- ポインタを使用した削除
	bool RemoveObject(ObjBase* _Obj)
	{
		for (auto p : m_Objlist)
		{
			if (p->GetidentNumb() != _Obj->GetidentNumb())
				continue;

			m_Objlist.remove(p);
			delete p;
			return true;
		}
		return false;
	}

	// ------------------------------
	// --- 固有番号を使用した削除
	bool RemoveObject(int _IdentNumb)
	{
		for (auto p : m_Objlist)
		{
			if (p->GetidentNumb() != _IdentNumb)
				continue;

			m_Objlist.remove(p);
			delete p;
			return true;
		}
		return false;
	}

	// ------------------------------
	// --- 初期化
	void Init() {
		for (auto p : m_Objlist)
		{
			p->Init();
		}
	};

	// ------------------------------
	// --- 更新
	void Update() {
		for (auto p : m_Objlist)
		{
			p->Update();
		}
	};

	// ------------------------------
	// --- あとから更新
	void LateUpdate() {
		for (auto p : m_Objlist)
		{
			p->LateUpdate();
		}
	};

	// ------------------------------
	// --- 描画
	void Draw() {
		for (auto p : m_Objlist)
		{
			p->Draw();
		}
	};

	// ------------------------------
	// --- あとから描画
	void LateDraw() {
		for (auto p : m_Objlist)
		{
			p->LateDraw();
		}
	};

	// ------------------------------
	// --- UI描画
	void UIDraw() {
		for (auto p : m_Objlist)
		{
			p->UIDraw();
		}
	};

	// ------------------------------
	// --- 終了
	void Release() {
		for (auto p : m_Objlist)
		{
			p->Release();
		}
	};

	// ------------------------------
	// --- 一時停止
	void Pause() {
		for (auto p : m_Objlist)
		{
			p->Pause();
		}
	};

	// ------------------------------
	// --- 削除しないObjの取得
	std::list<ObjBase*> GetExculdeObj() {

		std::list<ObjBase*> GetObj;

		for (auto itr = m_Objlist.begin(), end = m_Objlist.end(); itr != end;)
		{
			auto p = *itr;

			if (p->GetNonDestFlag())
			{
				GetObj.push_back(p);
				itr = m_Objlist.erase(itr);
			}
			else {
				++itr;
			}
		}
		return std::move(GetObj);
	};

private:
	std::list<ObjBase*> m_Objlist;	// 保存しているObj
};
#pragma endregion

#pragma region CObjMgr
class CObjMgr : public CSingleton<CObjMgr>
{
public:

	CObjMgr();
	~CObjMgr();

	void Init();
	void Update();
	void LateUpdate();
	void Draw();
	void LateDraw();
	void UIDraw();
	void Release();
	void Pause();

	bool PushObj(ObjBase* obj, UINT ID);
	bool PopObj(int Numb, int ID);
	std::list<ObjBase*> SerchObj(UINT ID);
	std::list<std::list<ObjBase*>>  ExculdeObj();
	void ObjMigration();

	friend class CSingleton<CObjMgr>;

private:
	std::array<ObjList*, MAX_ID> m_ObjListArray;			// Objname単位で確保されたlistを含んだ配列
	std::vector<std::pair<int, int>> m_HoldDeletelistpair;
	unsigned int m_Numb = 0;									// 固有番号
	bool ObjDeleteApply = false;
};
#pragma endregion
