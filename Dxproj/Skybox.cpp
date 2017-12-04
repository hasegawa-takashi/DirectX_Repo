#include "Skybox.h"



CSkybox::CSkybox()
{
	m_Position = D3DXVECTOR3(0, 0, 0);
	m_RenderModel = new CRenderModel("../data/model/sky.x");
	m_Bgm.Playercomp = m_Bgm.Comp.AddComponent<CSoundPlayerComponent>();
	m_Bgm.Sourcevoice = *(m_Bgm.Playercomp->Init("Bgm", "Bgm1"));
	m_Bgm.Playercomp->Play();
}


CSkybox::~CSkybox()
{
	m_Bgm.Comp.ClearComponent();
	delete m_RenderModel;
}

void CSkybox::Init()
{
}

void CSkybox::Update()
{
	m_Bgm.Comp.ComponentUpdate();
}

void CSkybox::Draw()
{
	m_RenderModel->RenderModel();
}

void CSkybox::Release()
{
}