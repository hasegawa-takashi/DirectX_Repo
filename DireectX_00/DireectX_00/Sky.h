// スカイドーム クラス定義

#pragma once

#include "ObjManager.h"
#include "Camera.h"
#include"MeshRender.h"

class CSky : public ObjBase
{
private:

	OBJMGR CameraObj;
	ColBox Collision;


public:
	CSky();
	virtual ~CSky(void);

	void Init();		// 初期化
	void Update();		// 更新
	void Draw();		// 描画
	void LateDraw();	// 半透明描画
	void UIDraw(){};
	void Fin();			// 解放

	void LateUpdate();
	void Release();
	void Pause(){};
	bool AllRelaseObj(){ return true; }
	
	//----------------------------------------
	// --- コリジョンの設定
	ColBox GetCol(){ return Collision; }


};