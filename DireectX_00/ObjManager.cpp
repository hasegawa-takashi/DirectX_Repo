
// --- インクルード
#include "ObjManager.h"
#include"Debug.h"
#include<math.h>
#include <queue>
#include <string>
#include <functional>


//-------------------------------------------------------
//
//	Objectのコンストラクタ
//
//-------------------------------------------------------
CObjManager::CObjManager()
{
	
	
	
}

//-------------------------------------------------------
//
//	Objectのデストラクタ
//
//-------------------------------------------------------
CObjManager::~CObjManager()
{
	AllRelaseObj();
}

//-------------------------------------------------------
//
//	Objectの初期化
//
//-------------------------------------------------------
void CObjManager::Init()
{
	
	// Objリストの初期化
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->Init();
	}
}

//-------------------------------------------------------
//
//	Objectの更新
//
//-------------------------------------------------------
void CObjManager::Update()
{
	// Objリストの初期化
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->Update();
	}

}

//-------------------------------------------------------
//
//	Objectの更新
//
//-------------------------------------------------------
void CObjManager::LateUpdate()
{
	// Objリストの初期化
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->LateUpdate();
	}

}

//-------------------------------------------------------
//
//	Objectの描画
//
//-------------------------------------------------------
void CObjManager::Draw()
{
	// Objリストの初期化
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->Draw();
	}

}

//-------------------------------------------------------
//
//	Objectの描画
//
//-------------------------------------------------------
void CObjManager::LateDraw()
{
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->LateDraw();
	}

	// ここでソートをかける
	//std::sort(TranslucentObj.begin(), TranslucentObj.end(), std::greater<std::pair<float, ObjBase*>>());

	// 半透明オブジェクトの描画
	for (auto itr = TranslucentObj.begin(); itr != TranslucentObj.end(); itr++)
	{
		
		itr->second->LateDraw();

		if (TranslucentObj.empty())
			return;
	}

}



//-------------------------------------------------------
//
//	Objectの描画
//
//-------------------------------------------------------
void CObjManager::UIDraw()
{

	// Objリストの描画
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->UIDraw();
	}

}

//-------------------------------------------------------
//
//	Objectのリリース
//		
//-------------------------------------------------------
void CObjManager::Release()
{
	// 多分これは必要ないと思う
	CObjManager::Instance()->AllRelaseObj();
}

//-------------------------------------------------------
//
//	Objectの捜索
//
//-------------------------------------------------------
list<ObjBase*> CObjManager::SerchObj(UINT ID)
{
	// 指定IDのobjlistを取得
	return m_ObjListArray[ID]->GetObjlist();

}

//-------------------------------------------------------
//
//	Objectの挿入
//
//-------------------------------------------------------
bool CObjManager::PushObj( ObjBase* obj , UINT ID)
{
	
	//==============================
	//
	//	何かしらの例外処理必要かね?
	//

	// オブジェクトの新規挿入
	m_ObjListArray[ID]->AddObject(obj);


}

//-------------------------------------------------------
//
//	Objectの削除
//
//-------------------------------------------------------
bool CObjManager::PopObj(int ID,int Identnumb)
{
	// Objリストの初期化
	return m_ObjListArray[ID]->RemoveObject(Identnumb);

}


//-------------------------------------------------------
//
//	Objectの交換
//
//-------------------------------------------------------
bool CObjManager::ChangeObj(int ID ,int IdentNumb, ObjBase* obj)
{
	
	m_ObjListArray[ID]->RemoveObject(IdentNumb);

	m_ObjListArray[ID]->AddObject(obj);
	

	return true;

}

//-------------------------------------------------------
//
//	Objectの全削除
//
//-------------------------------------------------------
bool CObjManager::AllRelaseObj()
{
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->AllDeleteObj();
	}
	Numb = 10;
	return true;

}

//-------------------------------------------------------
//
//	Objectの論理的削除
//
//-------------------------------------------------------
array<ObjList*, MAX_ID> CObjManager::ExculdeObj()
{

	array<ObjList*, MAX_ID> excludeObjlist;

	/*for (auto itr = ObjList.begin(); itr != ObjList.end(); itr++)
	{
		for (auto mapitr = itr->begin(); mapitr != itr->end();)
		{
			if ( mapitr->second->GetNonDestFlag() )
			{
				excludeObjlist.push_back(mapitr->second);
				mapitr = itr->erase(mapitr);
			}
			else
			{
				mapitr++;
			}

		}
	}*/

	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->GetExculdeObj();
	}

	return std::move(excludeObjlist);

}

//-------------------------------------------------------
//
//	Objectを命名するためのクラス
//  ちょっと面倒でポインタの位置を名前として使用
//	
//-------------------------------------------------------
int CObjManager::RenameObj(UINT ID , ObjName &SetObj)
{

	int name = 0;

	switch (ID)
	{
	case ID_PLAYER:
		name = Numb;
		SetObj = ID_PLAYER;
		break;

	case ID_ENEMY:
		name = Numb;
		SetObj = ID_ENEMY;
		break;

	case ID_FIELD:
		name = Numb; 
		SetObj = ID_FIELD;
		break;

	case ID_BALLET:
		name = Numb; 
		SetObj = ID_BALLET;
		break;

	case ID_CAMERA:
		name = Numb; 
		SetObj = ID_CAMERA;
		break;

	case ID_GOAL:
		name = Numb; 
		SetObj = ID_GOAL;
		break;

	case ID_OTHER:
		SetObj = ID_OTHER;
		name = Numb;
		break;

	case ID_FADE:
		SetObj = ID_FADE;
		name = Numb;
		break;

	default:
		break;
	}

	return name;

}

//-------------------------------------------------------
//
//	半透明オブジェクトの登録
//
//-------------------------------------------------------
bool CObjManager::LateRenderPush( ObjBase* render)
{
	
	D3DXVECTOR3 PosA = render->GetPos();

	float ABLength = CameraDistance(PosA);

	TranslucentObj.push_back( std::make_pair(ABLength,render) );

	return true;
}

//-------------------------------------------------------
//
//	View行列からカメラポジション
//
//-------------------------------------------------------
float CObjManager::CameraDistance(D3DXVECTOR3 SetPos)
{
	D3DXMATRIX ViewPos;
	GetDxMgr()->GetDxDevice()->GetTransform(D3DTS_VIEW, &ViewPos);
	D3DXMATRIX hoge = ViewPos;
	D3DXMatrixInverse(&hoge, NULL, &hoge);

	// カメラの現在のポジションの取得
	D3DXVECTOR3 vp{ hoge._41, hoge._42, hoge._43 };

	D3DXVECTOR3 VecDir = SetPos - vp;

	float result = D3DXVec3Length(&VecDir);

	return result;

}