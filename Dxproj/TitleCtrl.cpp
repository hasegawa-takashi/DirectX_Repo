#include "TitleCtrl.h"



CTitleCtrl::CTitleCtrl()
{
	for (int loop = 0; loop < MAX_TEXTURE_TITLE; ++loop)
	{
		auto p = new CSprite;
		m_Sprite[loop] = p;
	}

	m_Sprite[0]->CreateMakeVertex2DPolygon(_T("../data/Texture/Title.png"), 0, 0, 800, 600, 255);
	m_PushSceneChange = false;
}


CTitleCtrl::~CTitleCtrl()
{
	for (int i = 0; i < MAX_TEXTURE_TITLE; ++i)
	{
		if (m_Sprite[i] != nullptr)
		{
			m_Sprite[i]->Release();
			delete m_Sprite[i];
		}
	}
}

void CTitleCtrl::Update()
{
	if (CInput::GetKeyPress(DIK_SPACE) && m_PushSceneChange == false)
	{
		CSceneMgr::Getintance().PushScene<CGameScene>();
		CSceneMgr::Getintance().ChangeScene();
		m_PushSceneChange = true;
	}
}

void CTitleCtrl::UIDraw()
{
	for (int i = 0; i < MAX_TEXTURE_TITLE; i++)
	{
		m_Sprite[i]->Render();
	}
}