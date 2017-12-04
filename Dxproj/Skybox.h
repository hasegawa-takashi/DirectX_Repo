#pragma once
#include "includeheader.h"
#include"SoundInclude.h"

class CRenderModel;
#include"RenderModel.h"

class CSkybox :
	public ObjBase
{
public:
	CSkybox();
	~CSkybox();

	void Init();
	void Update();
	void Draw();
	void Release();

private:
	AudioComponent m_Bgm;
	CRenderModel* m_RenderModel;

};

