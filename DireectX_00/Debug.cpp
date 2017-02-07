#include "Debug.h"

#define SAFE_RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}


void CDebug::Init()
{
	//文字フォントの設定
	LPCWSTR Font = TEXT("tahoma");
	if (FAILED(D3DXCreateFont(CWindow::Instance()->GetDevice(), 14, 7, FW_BOLD, NULL, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, Font, &pFont)))
	{
		return;
	}
}

CDebug::~CDebug()
{
	SAFE_RELEASE(pFont);
}

void CDebug::Conversion(TCHAR szstr[], short value)
{
	str += szstr;

	_stprintf(Msg,_T("%d"),value);
	str += Msg;
}

void CDebug::Conversion(TCHAR szstr[], unsigned short value)
{
	str += szstr;
	_stprintf(Msg, _T("%d"), value);
	str += Msg;
}

void CDebug::Conversion(TCHAR szstr[], int value)
{
	str += szstr;
	_stprintf(Msg, _T("%d"), value);
	str += Msg;
}

void CDebug::Conversion(TCHAR szstr[], unsigned int value)
{
	str += szstr;
	_stprintf(Msg, _T("%d"), value);
	str += Msg;
}

void CDebug::Conversion(TCHAR szstr[], float value)
{
	str += szstr;
	_stprintf(Msg, _T("%.3lf"), value);
	str += Msg;
}

void CDebug::Conversion(TCHAR szstr[], double value)
{
	str += szstr;
	_stprintf(Msg, _T("%.3lf"), value);
	str += Msg;
}

void CDebug::Conversion(TCHAR szstr[], bool value)
{
	str += szstr;
	if (value)
	{
		str += _T("true");
	}
	else
	{
		str += _T("false");
	}
}


void CDebug::Conversion(TCHAR szstr[],D3DXVECTOR3 value)
{
	
	str += szstr;
	_stprintf(Msg, _T("%.3lf : %.3lf : %.3lf "), value.x,value.y,value.z);
	str += Msg;
}

void CDebug::Render()
{

	RECT rect = { 0,0,0,0 };

	pFont->DrawText(NULL, str.c_str(), -1, &rect, DT_LEFT | DT_CALCRECT, NULL);
	pFont->DrawText(NULL, str.c_str(), -1, &rect, DT_LEFT | DT_BOTTOM, 0xffffffff);

	str = _T(""); //空文字でクリア
}

void CDebug::Release()
{
	SAFE_RELEASE(pFont);
}