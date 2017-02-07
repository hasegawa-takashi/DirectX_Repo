#include "Score.h"


CScore::CScore(float left, float Right, float Top, float Bottom)
{
	rect = {  (LONG)left,  (LONG)Right,  (LONG)Top,  (LONG)Bottom };

	D3DXCreateFont(CWindow::Instance()->GetDevice(), 18, 5, FW_BOLD, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, _T("tahoma"), &m_Font);
}


CScore::~CScore()
{
}

void CScore::Draw(LPCWSTR str , int Numb,int max)
{
	TCHAR _str[256];

	wsprintf(_str, str, Numb, max);

	m_Font->DrawText(NULL, _str, -1, &rect, DT_NOCLIP, D3DCOLOR_ARGB(0, 255, 255, 0xff));
}


void CScore::Release()
{

}