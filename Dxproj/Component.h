#pragma once

/*
*
*	component������������C��
*	����SoundCompnent�����������͂�
*/
#include<list>
#include"Sound\AudioComponent\SoundComponent\SoundComponent.h"

class Component
{
public:

	Component() {};

	//  ^  ^
	//(' �� ' (^^ (^^ (^^ (^^ (^^ (^^ (^^ (^^ (^^ (^^ ) 
	//
	//	�f�X�g���N�^
	//
	~Component()
	{
	}

	void  ClearComponent()
	{
		for (auto itr = m_SoundComp.begin(); itr != m_SoundComp.end(); ++itr)
		{
			delete(*itr);
		}
		m_SoundComp.clear();
	}

	//  ^  ^
	//(' �� ' (^^ (^^ (^^ (^^ (^^ (^^ (^^ (^^ (^^ (^^ ) 
	//
	//	�A�b�v�f�[�g
	//
	void ComponentUpdate()
	{
		for (auto itr = m_SoundComp.begin(); itr != m_SoundComp.end(); ++itr)
		{
			(*itr)->ComponentUpdate();
		}
	}

	template<class Ty>
	Ty* AddComponent()
	{
		auto pComp = new Ty;
		m_SoundComp.push_back(pComp);
		return pComp;
	}

	void Remove(CSoundComponent* _comp)
	{
		m_SoundComp.remove(_comp);
		delete _comp;
	}

	template<class Ty>
	Ty* GetComponent()

	{
		for (auto itr = m_SoundComp.begin(); itr != m_SoundComp.end(); ++itr)
		{
			auto pCasted = dynamic_cast<Ty*>(_);
			if (nullptr != pCasted)
			{
				return pCasted;
			}
			return nullptr;
		}
	}

private:
	std::list<CSoundComponent*> m_SoundComp;

};

