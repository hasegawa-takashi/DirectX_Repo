// �X�J�C�h�[�� �N���X��`

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

	void Init();		// ������
	void Update();		// �X�V
	void Draw();		// �`��
	void LateDraw();	// �������`��
	void UIDraw(){};
	void Fin();			// ���

	void LateUpdate();
	void Release();
	void Pause(){};
	bool AllRelaseObj(){ return true; }
	
	//----------------------------------------
	// --- �R���W�����̐ݒ�
	ColBox GetCol(){ return Collision; }


};