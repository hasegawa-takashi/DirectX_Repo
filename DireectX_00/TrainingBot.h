#pragma once
#include "EnemyMgr.h"

class TrainingBot : public ObjBase
{
public:
	TrainingBot();
	~TrainingBot();

	void Init();
	void Update();
	void LateUpdate();
	void Draw();
	void LateDraw();
	void UIDraw(){};
	void Release();
	void Pause();
	bool AllRelaseObj();
	CMeshRender* GetRender();
	void SetidentNumb(int);
	int GetidentNumb();

	void SetPos(D3DXVECTOR3);

private:
	D3DXVECTOR3 m_Pos;
	ColBox Collision;

	BillbordPlate Billbord;
	CBillbord *billnprd;

};

