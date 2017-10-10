#pragma once
#include "includeheader.h"


const float NEAR_CLIP = 1.0f;
const float FAR_CLIP = 100.0f;
const float FOVY = 45.0f;

class CRenderFormat : public CSingleton<CRenderFormat>
{
public:
	CRenderFormat();
	~CRenderFormat();

	void Init();

	void TransmissionDraw();
	bool StartRender();
	void EndRender();

private:
	D3DXMATRIX m_MatView;
	D3DXMATRIX m_MatProj;
};

