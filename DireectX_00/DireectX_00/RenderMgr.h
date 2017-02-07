#pragma once
//////////////////////////////////////////////////////////////
//
//		RenderManafer
//			描画関数
//
/////////////////////////////////////////////////////////////

//	インクルード
#include"Window.h"
#include<list>
#include<vector>
//#include"Camera.h"


#define	NUM_VERTEX		(4)		// 頂点数
#define	NUM_POLYGON		(2)		// ポリゴン数

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

//////////////////////////////////////////////////////////////
//
//		CRenderMgr
//			描画を統括するあれ頑張って作成中
//
/////////////////////////////////////////////////////////////
class CRenderMgr 
{

public:
	~CRenderMgr();
	CRenderMgr(){};


	//---------------------------------------
	// オブジェクトマネージャーのインスタンス
	/*static CRenderMgr* Instance(void) {
		static CRenderMgr _instance;
		return &_instance;
	}*/

	//---------------------------------------
	// ライトの設定
	void LightMode();

	//---------------------------------------
	// 描画の初期化
	void Init();
	//---------------------------------------
	// 描画の終了処理
	void Relase(){};
	

private:
};



//====================================================================================
//									EOF
//====================================================================================
