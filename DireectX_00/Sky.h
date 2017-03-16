// �X�J�C�h�[�� �N���X��`

#pragma once

#include "ObjManager.h"
#include "Camera.h"
#include"MeshRender.h"

class CSky : public ObjBase
{
private:
	std::list<ObjBase*> CameraObj;	// �J����

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
	

};