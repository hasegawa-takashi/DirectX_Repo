#pragma once
#include "ObjManager.h"
#include"MeshRender.h"

class CField :public ObjBase
{
public:
	CField();
	~CField();
	//----------------------------
	// --- �I�u�W�F�N�g�̏�����
	void Init();
	//----------------------------
	// --- �I�u�W�F�N�g�̍X�V
	void Update();
	//----------------------------
	// --- �I�u�W�F�N�g�̍X�V(���Ƃ���p)c
	void LateUpdate(){};
	//----------------------------
	// --- �I�u�W�F�N�g�̕`��
	void Draw();
	//----------------------------------------
	// --- �I�u�W�F�N�g�̕`��(���Ƃ���p)
	void LateDraw(){};
	//----------------------------------------
	// --- �I�u�W�F�N�g�̕`��(���Ƃ���p)
	void UIDraw(){};
	//----------------------------
	// --- �I�u�W�F�N�g�̍폜
	void Release();
	//----------------------------
	// --- �|�[�Y���
	void Pause(){};
	//----------------------------
	// --- �ŏI�����S�폜�p
	bool AllRelaseObj(){ return true; };
	//----------------------------------------
	// --- �R���W�����̐ݒ�
	ColBox GetCol(){ return Collision; }
	
private:
	bool	m_bLoad;
	ColBox Collision;

};

