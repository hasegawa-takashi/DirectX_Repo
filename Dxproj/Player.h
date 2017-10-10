#pragma once
#include"includeheader.h"

class CRenderModel;
#include"RenderModel.h"

//class CRenderNonMesh;
//#include"RenderNonMesh.h"

class CPlayer : public ObjBase
{
public:
	CPlayer();
	~CPlayer();
	
	void Init();
	void Update();
	void Draw();
	void Release();

private:

	void Move();
	void MoveResult();

	enum Controller
	{
		Forwad = 0x00000001,
		Left = 0x00000010,
		Right = 0x00000100,
		Back = 0x00001000,
		FL = 0x00000011,
		FR = 0x00000101,
		BL = 0x00001010,
		BR = 0x00001100,
	};

	CRenderModel* m_PlayerModel;
	//CRenderNonMesh* m_PlayerModel;

	float m_MoveSpd;
	
	D3DXVECTOR3 m_Movement;
};