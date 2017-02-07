#pragma once
#include"Window.h"

class CScore
{
public:
	CScore(float left, float Right, float Top, float Bottom);
	~CScore();

	void Draw(LPCWSTR str, int Numb, int max);

	void Release();

private: 
	LPD3DXFONT m_Font;
	RECT rect;

};

