#pragma once

#include"includeheader.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <tchar.h>


class CDebug : public CSingleton<CDebug>
{
public:
	

	CDebug();


	~CDebug();

	void Init();

	void Render();

	void Release();

	//-------------------------
	// ---- Convert各種
	void Conversion(TCHAR szstr[],short value);
	void Conversion(TCHAR szstr[],unsigned short value);
	void Conversion(TCHAR szstr[],int value);
	void Conversion(TCHAR szstr[],unsigned int value);
	void Conversion(TCHAR szstr[],float value);
	void Conversion(TCHAR szstr[],double value);
	void Conversion(TCHAR szstr[],bool value);
	void Conversion(TCHAR szstr[],D3DXVECTOR3 value);


private:
	

	LPD3DXFONT pFont; // フォントオブジェクト
 	TCHAR Msg[256];	  // メッセージ内容

#if _UNICODE
	std::wstring str;			// デバッグ文字列保持バッファ（UNICODE用）
#else
	std::string str;				// デバッグ文字列保持バッファ（ANCI用）
#endif
};

