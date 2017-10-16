#pragma once

#pragma region ObjBase
#include<d3dx9.h>

// ---------------------------------------
// --- �Q�[����Obj�Ɍp������x�[�X�N���X
class ObjBase
{
protected:
	int m_ObjNumb;					// �ŗLID
	int m_ObjID;					// enum :: ObjName
	bool m_NonDeleteObj = false;	// �j��s��Obj
	D3DXVECTOR3 m_Position;			// ���W(X,Y,Z)
	D3DXMATRIX m_WorldMtx;			// Obj�̃��[���h�s��

public:
	ObjBase(){}
	virtual ~ObjBase(){}

	virtual void Init() {}			// ������
	virtual void Update() {}		// �X�V
	virtual void LateUpdate() {}	// ���̂܂��
	virtual void Draw() {}			// �`��
	virtual void LateDraw() {}		// ���̂܂��
	virtual void UIDraw() {}		// UI�`��
	virtual void Release() {}		// �폜	
	virtual void Pause() {}			// �|�[�Y��

	virtual void SetidentNumb(int ID) { m_ObjNumb = ID; }		// �ŗL�ԍ��̃Z�b�g
	virtual int GetidentNumb() { return m_ObjNumb; }			// �ŗL�ԍ��̎擾
	virtual bool GetNonDestFlag() { return m_NonDeleteObj; }	// �j�󂵂Ȃ�Obj�̎擾
	virtual int GetObjID() { return m_ObjID; }					// ObjName�̎擾
	virtual D3DXVECTOR3 GetPosition() { return m_Position; }	// ���W�̎擾
};
#pragma endregion

#include"includeheader.h"

// --------------------
// --- ID�̎��
enum ObjName
{
	ID_PLAYER = 0,	// �v���C���[�p�̔ԍ�
	ID_OTHER,		// ���̑��̔ԍ�
	ID_FADE,		// Fade�p�I�u�W�F�N�g
	MAX_ID
};


#pragma region Objlist
// --------------------------------
// --- �Q�[���I�u�W�F�N�g���Ǘ����郊�X�g
class ObjList
{
public:

	// --------------------
	// --- �R���X�g���N�g
	ObjList(){}

	// --------------------
	// --- �f�X�g���N�^
	virtual ~ObjList(){
		if (m_Objlist.empty())
		{
			for (auto& _Obj : m_Objlist)
				delete _Obj;
		}
	}

	// ------------------------------
	// --- List���ɓ����Ă�Obj�̎擾
	std::list<ObjBase*> GetObjList()
	{
		return m_Objlist;
	}

	// ------------------------------
	// --- �I�u�W�F�N�g�̒ǉ�
	void AddObject(ObjBase* _Obj)
	{
		m_Objlist.push_back(_Obj);
	}

	// ------------------------------
	// --- �|�C���^���g�p�����폜
	bool RemoveObject(ObjBase* _Obj)
	{
		for (auto p : m_Objlist)
		{
			if (p->GetidentNumb() != _Obj->GetidentNumb())
				continue;

			m_Objlist.remove(p);
			delete p;
			return true;
		}
		return false;
	}

	// ------------------------------
	// --- �ŗL�ԍ����g�p�����폜
	bool RemoveObject(int _IdentNumb)
	{
		for (auto p : m_Objlist)
		{
			if (p->GetidentNumb() != _IdentNumb)
				continue;

			m_Objlist.remove(p);
			delete p;
			return true;
		}
		return false;
	}

	// ------------------------------
	// --- ������
	void Init() {
		for (auto p : m_Objlist)
		{
			p->Init();
		}
	};

	// ------------------------------
	// --- �X�V
	void Update() {
		for (auto p : m_Objlist)
		{
			p->Update();
		}
	};

	// ------------------------------
	// --- ���Ƃ���X�V
	void LateUpdate() {
		for (auto p : m_Objlist)
		{
			p->LateUpdate();
		}
	};

	// ------------------------------
	// --- �`��
	void Draw() {
		for (auto p : m_Objlist)
		{
			p->Draw();
		}
	};

	// ------------------------------
	// --- ���Ƃ���`��
	void LateDraw() {
		for (auto p : m_Objlist)
		{
			p->LateDraw();
		}
	};

	// ------------------------------
	// --- UI�`��
	void UIDraw() {
		for (auto p : m_Objlist)
		{
			p->UIDraw();
		}
	};

	// ------------------------------
	// --- �I��
	void Release() {
		for (auto p : m_Objlist)
		{
			p->Release();
		}
	};

	// ------------------------------
	// --- �ꎞ��~
	void Pause() {
		for (auto p : m_Objlist)
		{
			p->Pause();
		}
	};

	// ------------------------------
	// --- �폜���Ȃ�Obj�̎擾
	std::list<ObjBase*> GetExculdeObj() {

		std::list<ObjBase*> GetObj;

		for (auto itr = m_Objlist.begin(), end = m_Objlist.end(); itr != end;)
		{
			auto p = *itr;

			if (p->GetNonDestFlag())
			{
				GetObj.push_back(p);
				itr = m_Objlist.erase(itr);
			}
			else {
				++itr;
			}
		}
		return std::move(GetObj);
	};

private:
	std::list<ObjBase*> m_Objlist;	// �ۑ����Ă���Obj
};
#pragma endregion

#pragma region CObjMgr
class CObjMgr : public CSingleton<CObjMgr>
{
public:

	CObjMgr();
	~CObjMgr();

	void Init();
	void Update();
	void LateUpdate();
	void Draw();
	void LateDraw();
	void UIDraw();
	void Release();
	void Pause();

	bool PushObj(ObjBase* obj, UINT ID);
	bool PopObj(int Numb, int ID);
	std::list<ObjBase*> SerchObj(UINT ID);
	std::list<std::list<ObjBase*>>  ExculdeObj();
	void ObjMigration();

	friend class CSingleton<CObjMgr>;

private:
	std::array<ObjList*, MAX_ID> m_ObjListArray;			// Objname�P�ʂŊm�ۂ��ꂽlist���܂񂾔z��
	std::vector<std::pair<int, int>> m_HoldDeletelistpair;
	unsigned int m_Numb = 0;									// �ŗL�ԍ�
	bool ObjDeleteApply = false;
};
#pragma endregion
