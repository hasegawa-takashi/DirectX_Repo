#pragma once
//////////////////////////////////////////////////////////////
//
//		RenderManafer
//			描画関数
//
/////////////////////////////////////////////////////////////

//	インクルード
#include"Window.h"
#include"DxDevice.h"

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
	~CRenderMgr() {};

	CRenderMgr() {};
	//---------------------------------------
	// オブジェクトマネージャーのインスタンス
	static CRenderMgr* Instance(void) {
		static CRenderMgr _instance;
		return &_instance;
	}

	//---------------------------------------
	// 描画の初期化
	void Init();
	
	//---------------------------------------
	// 描画前の準備
	void  RenderTransStart();
	//---------------------------------------
	// 描画前の終了
	void  RenderEnd();

private:

	D3DXMATRIX	m_MatView;		// ビュー マトリックス
	D3DXMATRIX	m_MatProj;		// 射影マトリックス

};

//=============================================================================
// デバイス呼び出し用
//=============================================================================
inline CRenderMgr* GetRenderMgr()
{
	return CRenderMgr::Instance();
}

//====================================================================================
//									EOF
//====================================================================================
