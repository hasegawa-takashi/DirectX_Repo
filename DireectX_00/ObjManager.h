#pragma once

// �C���N���[�h
#include<list>
#include<map>
#include<string>
#include<vector>

#include"MeshRender.h"

// �O���[�o��

// �N���X��`

enum ObjName
{
	ID_PLAYER = 0,	// �v���C���[�p�̔ԍ�
	ID_ENEMY,		// �G�l�~�[�p�̔ԍ�
	ID_FIELD,		// �t�B�[���h�p�̔ԍ�
	ID_BALLET,		// �o���b�g�p�̔ԍ�
	ID_CAMERA,		// �J�����p
	ID_GOAL,		// �S�[���p
	ID_OTHER,		// ���̑��̔ԍ�
	MAX_ID
};

enum CollisionType
{
	COL_SPHERE,		// ��::��
	COL_AABB,		// AABB::AABB
	COL_OBB,		// OBB::OBB
	COL_RAY,		// RAY::MESH
	COL_RAY_SPHERE,	// RAY::��
	COL_RAY_OBB,	// RAY::OBB
	MAX_COL
};

//////////////////////////////////////////////////////////////
//
//		ColBox
//			�����̊֌W�ケ���ɕ`���B
//			�����蔻�����������I�u�W�F�N�g�ɂ͕ێ������邱��
//
/////////////////////////////////////////////////////////////
class ColBox{

public:
	// OBB����
	D3DXVECTOR3 m_Pos;              // �ʒu
	D3DXVECTOR3 m_NormaDirect[3];   // �����x�N�g��
	FLOAT m_fLength[3];             // �e�������̒���
	float Radius;					// ���a
	D3DXMATRIX WorldMtx;			// ���[���h�}�g���N�Xs
	D3DXVECTOR3 Ray;				// ���C�̕���
	D3DXVECTOR3 ResultPos;			// �����n�_�̌��ʂ��擾
	int m_SetObjId;					// �Ώۂ̃��b�V��
	int IdentNumb;					// �ŗL�i���o�[

	std::multimap<int, int> Obj;	// �I�u�W�F�N�g�̌ŗL�ԍ�

};


//////////////////////////////////////////////////////////////
//
//		objectbase
//			���΂��΂����ǃQ�[�����I�u�W�F�N�g�p�̊Ǘ��N���X
//
/////////////////////////////////////////////////////////////
class ObjBase
{
public:
	ObjBase(){}
	virtual ~ObjBase(){}

	// === �p�����郁�b�Z�[�W === //

	// ���ꂼ��̍X�V�����̂��ߕK�{
	virtual void Init() {};
	virtual void Update() {};
	virtual void LateUpdate() {};
	virtual void Draw() {};
	virtual void LateDraw() {};
	virtual void UIDraw() {};
	virtual void Release() {};
	virtual void Pause() {};
	virtual bool AllRelaseObj() { return true; }

	// ��������\�����������
	virtual ColBox GetCol() = 0;

	// ��̌ŗL�ł������
	virtual CMeshRender* GetRender(){ return m_ModelMesh; }
	virtual void SetidentNumb(int ID){ ObjNumb = ID; }
	virtual int GetidentNumb(){ return ObjNumb; }
	virtual void SetPos(D3DXVECTOR3 pos){ m_Pos = pos; }
	virtual D3DXVECTOR3 GetPos(){ return m_Pos; }

protected:

	// === �p���p���b�Z�[�W === //

	D3DXMATRIX m_mtxWorld;		// ���[���h�s��
	CMeshRender *m_ModelMesh;	// ���f���`��p
	int ObjNumb;				// ���f���̌ŗL�ԍ�
	D3DXVECTOR3 m_Pos;			// �|�W�V����

};

typedef std::multimap< int, ObjBase* > OBJMGR;
typedef std::vector<std::pair<float, ObjBase*> > RenderSort;
//////////////////////////////////////////////////////////////
//
//		objectmanager
//			���΂��΂����ǃQ�[�����I�u�W�F�N�g�p�̊Ǘ��N���X
//
/////////////////////////////////////////////////////////////
class CObjManager
{
public:
	//----------------------------
	// �f�X�g���N�^
	~CObjManager();

	//---------------------------------------
	// �I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X
	static CObjManager* Instance(void) {
		static CObjManager _instance;
		return &_instance;
	}

	//----------------------------
	// --- �I�u�W�F�N�g�̏�����
	void Init();
	//----------------------------
	// --- �I�u�W�F�N�g�̍X�V
	void Update();
	//----------------------------
	// --- �I�u�W�F�N�g�̍X�V
	void LateUpdate();
	//----------------------------
	// --- �I�u�W�F�N�g�̕`��
	void Draw();
	//----------------------------
	// --- �I�u�W�F�N�g�̕`��
	void LateDraw();
	//----------------------------
	// --- UI�̕`��
	void UIDraw();
	//----------------------------
	// --- �I�u�W�F�N�g�̍폜
	void Release();
	//----------------------------
	// --- �I�u�W�F�N�g�̑S�폜
	bool AllRelaseObj();
	

	// === �����܂ŃI�u�W�F�N�g���� === //

	// === ��������I�u�W�F�N�g�Ǘ����� === //
	// === �I���폜���Ȃ����ƂɋC�t�������̍� === //

	//----------------------------
	// --- �I�u�W�F�N�g�̑}��
	bool PushObj(ObjBase* obj, UINT ID);

	//----------------------------
	// --- �I�u�W�F�N�g�̍폜
	bool PopObj(int Numb , int ID);

	//----------------------------
	// --- �I�u�W�F�N�g�̌���
	bool ChangeObj(int Numb, ObjBase*);

	//---------------------------
	// --- �I�u�W�F�N�g�ւ̖���
	// --- �F�X�����Ă���Ȃ��\�����o�Ă���
	int RenameObj(UINT ID);
	
	//---------------------------
	// --- �I�u�W�F�N�g�̑{��
	void SerchObj(UINT ID, OBJMGR& obj);
	
	//--------------------------------
	// --- �ǂ����悤���Ȃ����̏�����
	void MonSter(){ Numb = 0;  }

	// === ��������p���̕ϐ��錾 === //
	CMeshRender *m_ModelMesh;	// �`��p�̕ϐ��N���X

	// === ��������擖���蔻��֌W === //
	// === ��肢�������킩��Ȃ������̂ł����ňꊇ�œ����蔻����\�� === //

	//--------------------------------------
	// --- �I�u�W�F�N�g�̌����p+�����
	// --- ������ :: �T���I�u�W�F�N�g��ID
	// --- ������ :: �����̕��@
	bool CollisonCheck(UINT ID, int Colltype,ColBox &obb1);
	float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0);

	//---------------------------
	// --- OBB�̈��������Ă���ݒ�
	ColBox GetCol() {};

	// === ���������`��n === //
	CMeshRender* GetRender() {};

	// === �`��⏕�p === //
	// --- ������Obj�̃��X�g
	bool LateRenderPush(ObjBase* render);

private:

	//----------------------------
	// --- ���̔���
	bool CollisionBSphere(ColBox &obb1, ColBox &obb2);

	//----------------------------
	// --- AABB����
	bool CollisionAABB(ObjBase* pObj, UINT ID);

	//----------------------------
	// --- OBB����
	bool CollisionOBB(ColBox &obb1, ColBox &obb2);

	//----------------------------
	// --- Ray+Spher
	bool calcRaySphere(ColBox &obb1, ColBox &obb2);

	//----------------------------
	// --- �J�����Ƃ̋������o��
	float CameraDistance(D3DXVECTOR3 SetPos);

private:
	std::list< OBJMGR > ObjList;			// �I�u�W�F�N�g��list�\��
	RenderSort TranslucentObj;		// ������Obj���܂Ƃ߂Ă�list

	int Numb;
};

//=============================================================================
// �f�o�C�X�Ăяo���p
//=============================================================================
inline CObjManager* GetObjMgr()
{
	return CObjManager::Instance();
}


//====================================================================================
//									EOF
//====================================================================================
