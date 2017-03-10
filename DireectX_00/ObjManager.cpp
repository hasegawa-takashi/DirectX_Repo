
// --- �C���N���[�h
#include "ObjManager.h"
#include"Debug.h"
#include<math.h>
#include <queue>
#include <string>
#include <functional>


//-------------------------------------------------------
//
//	Object�̃R���X�g���N�^
//
//-------------------------------------------------------
CObjManager::CObjManager()
{
	
	
	
}

//-------------------------------------------------------
//
//	Object�̃f�X�g���N�^
//
//-------------------------------------------------------
CObjManager::~CObjManager()
{
	AllRelaseObj();
}

//-------------------------------------------------------
//
//	Object�̏�����
//
//-------------------------------------------------------
void CObjManager::Init()
{
	
	// Obj���X�g�̏�����
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->Init();
	}
}

//-------------------------------------------------------
//
//	Object�̍X�V
//
//-------------------------------------------------------
void CObjManager::Update()
{
	// Obj���X�g�̏�����
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->Update();
	}

}

//-------------------------------------------------------
//
//	Object�̍X�V
//
//-------------------------------------------------------
void CObjManager::LateUpdate()
{
	// Obj���X�g�̏�����
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->LateUpdate();
	}

}

//-------------------------------------------------------
//
//	Object�̕`��
//
//-------------------------------------------------------
void CObjManager::Draw()
{
	// Obj���X�g�̏�����
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->Draw();
	}

}

//-------------------------------------------------------
//
//	Object�̕`��
//
//-------------------------------------------------------
void CObjManager::LateDraw()
{
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->LateDraw();
	}

	// �����Ń\�[�g��������
	//std::sort(TranslucentObj.begin(), TranslucentObj.end(), std::greater<std::pair<float, ObjBase*>>());

	// �������I�u�W�F�N�g�̕`��
	for (auto itr = TranslucentObj.begin(); itr != TranslucentObj.end(); itr++)
	{
		
		itr->second->LateDraw();

		if (TranslucentObj.empty())
			return;
	}

}



//-------------------------------------------------------
//
//	Object�̕`��
//
//-------------------------------------------------------
void CObjManager::UIDraw()
{

	// Obj���X�g�̕`��
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->UIDraw();
	}

}

//-------------------------------------------------------
//
//	Object�̃����[�X
//		
//-------------------------------------------------------
void CObjManager::Release()
{
	// ��������͕K�v�Ȃ��Ǝv��
	CObjManager::Instance()->AllRelaseObj();
}

//-------------------------------------------------------
//
//	Object�̑{��
//
//-------------------------------------------------------
list<ObjBase*> CObjManager::SerchObj(UINT ID)
{
	// �w��ID��objlist���擾
	return m_ObjListArray[ID]->GetObjlist();

}

//-------------------------------------------------------
//
//	Object�̑}��
//
//-------------------------------------------------------
bool CObjManager::PushObj( ObjBase* obj , UINT ID)
{
	
	//==============================
	//
	//	��������̗�O�����K�v����?
	//

	// �I�u�W�F�N�g�̐V�K�}��
	m_ObjListArray[ID]->AddObject(obj);


}

//-------------------------------------------------------
//
//	Object�̍폜
//
//-------------------------------------------------------
bool CObjManager::PopObj(int ID,int Identnumb)
{
	// Obj���X�g�̏�����
	return m_ObjListArray[ID]->RemoveObject(Identnumb);

}


//-------------------------------------------------------
//
//	Object�̌���
//
//-------------------------------------------------------
bool CObjManager::ChangeObj(int ID ,int IdentNumb, ObjBase* obj)
{
	
	m_ObjListArray[ID]->RemoveObject(IdentNumb);

	m_ObjListArray[ID]->AddObject(obj);
	

	return true;

}

//-------------------------------------------------------
//
//	Object�̑S�폜
//
//-------------------------------------------------------
bool CObjManager::AllRelaseObj()
{
	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->AllDeleteObj();
	}
	Numb = 10;
	return true;

}

//-------------------------------------------------------
//
//	Object�̘_���I�폜
//
//-------------------------------------------------------
array<ObjList*, MAX_ID> CObjManager::ExculdeObj()
{

	array<ObjList*, MAX_ID> excludeObjlist;

	/*for (auto itr = ObjList.begin(); itr != ObjList.end(); itr++)
	{
		for (auto mapitr = itr->begin(); mapitr != itr->end();)
		{
			if ( mapitr->second->GetNonDestFlag() )
			{
				excludeObjlist.push_back(mapitr->second);
				mapitr = itr->erase(mapitr);
			}
			else
			{
				mapitr++;
			}

		}
	}*/

	for (size_t loop = 0; loop < m_ObjListArray.size(); loop++)
	{
		m_ObjListArray[loop]->GetExculdeObj();
	}

	return std::move(excludeObjlist);

}

//-------------------------------------------------------
//
//	Object�𖽖����邽�߂̃N���X
//  ������Ɩʓ|�Ń|�C���^�̈ʒu�𖼑O�Ƃ��Ďg�p
//	
//-------------------------------------------------------
int CObjManager::RenameObj(UINT ID , ObjName &SetObj)
{

	int name = 0;

	switch (ID)
	{
	case ID_PLAYER:
		name = Numb;
		SetObj = ID_PLAYER;
		break;

	case ID_ENEMY:
		name = Numb;
		SetObj = ID_ENEMY;
		break;

	case ID_FIELD:
		name = Numb; 
		SetObj = ID_FIELD;
		break;

	case ID_BALLET:
		name = Numb; 
		SetObj = ID_BALLET;
		break;

	case ID_CAMERA:
		name = Numb; 
		SetObj = ID_CAMERA;
		break;

	case ID_GOAL:
		name = Numb; 
		SetObj = ID_GOAL;
		break;

	case ID_OTHER:
		SetObj = ID_OTHER;
		name = Numb;
		break;

	case ID_FADE:
		SetObj = ID_FADE;
		name = Numb;
		break;

	default:
		break;
	}

	return name;

}

//-------------------------------------------------------
//
//	�������I�u�W�F�N�g�̓o�^
//
//-------------------------------------------------------
bool CObjManager::LateRenderPush( ObjBase* render)
{
	
	D3DXVECTOR3 PosA = render->GetPos();

	float ABLength = CameraDistance(PosA);

	TranslucentObj.push_back( std::make_pair(ABLength,render) );

	return true;
}

//-------------------------------------------------------
//
//	View�s�񂩂�J�����|�W�V����
//
//-------------------------------------------------------
float CObjManager::CameraDistance(D3DXVECTOR3 SetPos)
{
	D3DXMATRIX ViewPos;
	GetDxMgr()->GetDxDevice()->GetTransform(D3DTS_VIEW, &ViewPos);
	D3DXMATRIX hoge = ViewPos;
	D3DXMatrixInverse(&hoge, NULL, &hoge);

	// �J�����̌��݂̃|�W�V�����̎擾
	D3DXVECTOR3 vp{ hoge._41, hoge._42, hoge._43 };

	D3DXVECTOR3 VecDir = SetPos - vp;

	float result = D3DXVec3Length(&VecDir);

	return result;

}