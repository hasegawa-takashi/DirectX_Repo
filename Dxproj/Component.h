#pragma once

/*
*
*	component周りをもう一回修復
*	多分SoundCompnentがおかしいはず
*/
#include<list>
#include"Sound\AudioComponent\SoundComponent\SoundComponent.h"

class Component
{
public:

	Component() {};

	//  ^  ^
	//(' ω ' (^^ (^^ (^^ (^^ (^^ (^^ (^^ (^^ (^^ (^^ ) 
	//
	//	デストラクタ
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
	//(' ω ' (^^ (^^ (^^ (^^ (^^ (^^ (^^ (^^ (^^ (^^ ) 
	//
	//	アップデート
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

