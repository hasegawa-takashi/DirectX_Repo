#pragma once
#include "includeheader.h"

class CRenderModel;
#include"RenderModel.h"

class CTunnel : public ObjBase
{
public:
	CTunnel();
	~CTunnel();

	void Draw();
	void Update();

private:

	void Move();
	void MoveResult();
	void AutoDestroy();

	float m_MoveSpd;

	ColBox*	m_Collision;
	CRenderModel* m_RenderModel;
	D3DXVECTOR3 m_Movement;
	D3DXVECTOR3 m_Velocity;
};

