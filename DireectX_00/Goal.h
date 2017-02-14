#pragma once
#include"ObjManager.h"

class CGoal : public ObjBase
{
public:
	CGoal();
	~CGoal();

	void Init();
	void Update();
	void LateUpdate();
	void Draw();
	void LateDraw();
	void UIDraw(){};
	void Release();
	void Pause();


	bool AllRelaseObj(){ return true; };

	ColBox GetCol(){ return Collision; }

	CMeshRender* GetRender(){ return m_ModelMesh; }

	void SetPos(D3DXVECTOR3 pos){ m_Pos = pos; }

	void SetidentNumb(int ID){ ObjNumb = ID; }
	
	int GetidentNumb(){ return ObjNumb; }

private:
	ColBox Collision;			// “–‚½‚è”»’è—p
	D3DXVECTOR3 m_Pos;
};

