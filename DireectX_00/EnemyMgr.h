#pragma once

#include"ObjManager.h"
#include"Billbord.h"
#include<list>
#define MAX_BOT (4)

class CEnemyMgr : public ObjBase
{
public:
	CEnemyMgr();
	~CEnemyMgr();
	
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();
	virtual void LateDraw();
	virtual void UIDraw(){};
	virtual void Release();
	virtual void Pause();
	virtual bool AllRelaseObj();
	virtual ColBox GetCol();
	virtual CMeshRender* GetRender();
	virtual void SetidentNumb(int);
	virtual int GetidentNumb();
	void SetPos(D3DXVECTOR3 pos){ m_mtxWorld._41 = pos.x; m_mtxWorld._42 = pos.y; m_mtxWorld._43 = pos.z; }

	D3DXVECTOR3 m_Pos;
	ColBox Collision;
private:
	//std::list<int> EnemyNumb;
	D3DXVECTOR3 InitPos[MAX_BOT];

};

