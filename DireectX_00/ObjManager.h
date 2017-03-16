#pragma once

// �C���N���[�h
#include<list>
#include<map>
#include<string>
#include<vector>
#include<memory>
#include<array>
#include"MeshRender.h"
#include"Collision.h"

// 
using namespace std;

// ID�̎��
enum ObjName
{
	ID_PLAYER = 0,	// �v���C���[�p�̔ԍ�
	ID_ENEMY,		// �G�l�~�[�p�̔ԍ�
	ID_FIELD,		// �t�B�[���h�p�̔ԍ�
	ID_BALLET,		// �o���b�g�p�̔ԍ�
	ID_CAMERA,		// �J�����p
	ID_GOAL,		// �S�[���p
	ID_OTHER,		// ���̑��̔ԍ�
	ID_FADE,		// Fade�p�I�u�W�F�N�g
	MAX_ID
};

/*
OBJMGR�̍\��
-------	 -------
|  ID   |	|       |
|	+   |---|OBJBase|�E�E�E�E�E�E�E�E
|OBJBase|	|       |
-------	 -------
|
-------	 -------
|  ID   |	|       |
|	+   |---|OBJBase|�E�E�E�E�E�E�E�E
|OBJBase|	|       |
-------	 -------
*/

//////////////////////////////////////////////////////////////
//
//		ObjBase
//			���΂��΂����ǃQ�[�����I�u�W�F�N�g�p�̊Ǘ��N���X
//
/////////////////////////////////////////////////////////////
class ObjBase
{
protected:

	// === �p���p���b�Z�[�W === //
	ColBox m_Collision;			// �����蔻��p
	D3DXMATRIX m_mtxWorld;		// ���[���h�s��
	CMeshRender *m_ModelMesh;	// ���f���`��p
	int ObjNumb;				// ���f���̌ŗL�ԍ�
	ObjName ObjID;				// ���f����ID�ԍ�
	D3DXVECTOR3 m_Pos;			// �|�W�V����
	bool NonDeleteObj = false;	// �j��s��Obj

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
	virtual ColBox GetCol() {};

	// ��̌ŗL�ł������
	virtual CMeshRender* GetRender(){ return m_ModelMesh; }
	virtual void SetidentNumb(int ID){ ObjNumb = ID; }
	virtual int GetidentNumb(){ return ObjNumb; }
	virtual void SetPos(D3DXVECTOR3 pos){ m_Pos = pos; }
	virtual D3DXVECTOR3 GetPos(){ return m_Pos; }
	virtual bool GetNonDestFlag() { return NonDeleteObj; }
	virtual int GetIDNumb() { return (int)ObjID; }

};

//////////////////////////////////////////////////////////////
//
//		ObjList
//			���΂��΂����ǃQ�[�����I�u�W�F�N�g�p�̊Ǘ��N���X
//
/////////////////////////////////////////////////////////////
class ObjList
{

public:
	// �R���X�g���N�^
	ObjList() {}

	// �f�X�g���N�^
	virtual ~ObjList() {
		for (auto& pObj : m_ObjList)
			delete pObj;
	}

	//======================================
	//
	//	list��Getter
	//
	//======================================
	list<ObjBase*> GetObjlist()
	{
		return m_ObjList;
	}

	//======================================
	//
	//	ObjList�֒ǉ�
	//
	//======================================
	void AddObject(ObjBase* pObj)
	{
		m_ObjList.push_back(pObj);
	}


	//======================================
	//
	//	�ŗLID��T����Obj���X�g����폜
	//
	//
	//======================================
	bool RemoveObject(ObjBase* pObj)
	{
		for (auto p : m_ObjList)
		{
			if (p->GetidentNumb() != pObj->GetidentNumb())
				continue;

			m_ObjList.remove(p);
			delete p;
			return true;

		}

		return false;

	}
	
	bool RemoveObject(int IdentNumb)
	{
		for (auto p : m_ObjList)
		{
			if (p->GetidentNumb() != IdentNumb)
				continue;

			m_ObjList.remove(p);
			delete p;
			return true;

		}

		return false;
	}

	//----------------------------
	// --- �I�u�W�F�N�g�̏�����
	void Init() {

		for (auto p : m_ObjList)
		{
			p->Init();
		}

	};

	//----------------------------
	// --- �I�u�W�F�N�g�̍X�V
	void Update() {

		for (auto p : m_ObjList)
		{
			p->Update();
		}

	};

	//----------------------------
	// --- �I�u�W�F�N�g�̍X�V
	void LateUpdate() {

		for (auto p : m_ObjList)
		{
			p->LateUpdate();
		}

	};

	//----------------------------
	// --- �I�u�W�F�N�g�̕`��
	void Draw() {

		for (auto p : m_ObjList)
		{
			p->Draw();
		}

	};

	//----------------------------
	// --- �I�u�W�F�N�g�̕`��
	void LateDraw() {

		for (auto p : m_ObjList)
		{
			p->LateDraw();
		}

	};
	
	//----------------------------
	// --- UI�̕`��
	void UIDraw() {

		for (auto p : m_ObjList)
		{
			p->UIDraw();
		}

	};
	
	//----------------------------
	// --- �I�u�W�F�N�g�̍폜
	void Release() {

		for (auto p : m_ObjList)
		{
			p->Release();
		}

	};
	
	//----------------------------
	// --- �I�u�W�F�N�g�̑S�폜
	bool AllDeleteObj() {

		for (auto p : m_ObjList)
		{
			p->AllRelaseObj();
			delete p;
		}

		return true;

	};

	//----------------------------
	// --- �j��t���O�̎擾
	std::list<ObjBase*> GetExculdeObj() {

		std::list<ObjBase*> GetObj;

		for (auto p : m_ObjList)
		{
			if( p->GetNonDestFlag() )
				GetObj.push_back(p);
		}

		return GetObj;

	};

private:
	list<ObjBase*> m_ObjList;
};

// �ォ��`�悷����̂̐ݒ�
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
	bool ChangeObj(int ID, int IdentNumb, ObjBase*);

	//---------------------------
	// --- �I�u�W�F�N�g�ւ̖���
	// --- �F�X�����Ă���Ȃ��\�����o�Ă���
	int RenameObj(UINT ID, ObjName &SetObj);
	
	//---------------------------
	// --- �I�u�W�F�N�g�̑{��
	list<ObjBase*> SerchObj(UINT ID);
	
	//-----------------------------------------------------------
	// --- �I�u�W�F�N�g�̃|�C���^�����X�g����O��
	/* ���O�t���O�̗����Ă���I�u�W�F�N�g��List����O���A
		���̏��O�I�u�W�F�N�g�����X�g�ɂ��ĕԂ�*/
	std::list<std::list<ObjBase*>>  ExculdeObj();

	//--------------------------------
	// --- �ǂ����悤���Ȃ����̏�����
	//void MonSter(){ Numb = 0;  }

	// === ��������p���̕ϐ��錾 === //
	CMeshRender *m_ModelMesh;	// �`��p�̕ϐ��N���X

	// === ���������`��n === //
	CMeshRender* GetRender() {};

	// === �`��⏕�p === //
	// --- ������Obj�̃��X�g
	bool LateRenderPush(ObjBase* render);

private:

	//----------------------------
	// �R���X�g���N�^
	CObjManager();

	//----------------------------
	// --- �J�����Ƃ̋������o��
	float CameraDistance(D3DXVECTOR3 SetPos);

private:
	RenderSort TranslucentObj;		// ������Obj���܂Ƃ߂Ă�list

	array<ObjList*,MAX_ID> m_ObjListArray;	//

	unsigned int Numb = 10;						// �ŗLID�p
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
