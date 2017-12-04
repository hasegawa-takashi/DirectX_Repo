#pragma once
#include "includeheader.h"
#include"GameHeader.h"

class CRenderModel;
#include"RenderModel.h"

class ColBox;
#include"Collision.h"

class CEnemy : public ObjBase
{
public:
	CEnemy(float spd);
	~CEnemy();

	void Init();
	void Update();
	void Draw();
	void Release();

private:
	void HitEnemy();
	void Move();
	void MoveResult();
	void AutoDestroy();

	float m_MoveSpd;

	ColBox*	m_Collision;
	CRenderModel* m_RenderModel;
	D3DXVECTOR3 m_Movement;
	D3DXVECTOR3 m_Velocity;

	AudioComponent m_CrossSound;

	AudioComponent m_FallVoice;

	std::list<ObjBase*> m_HitObj;
};

