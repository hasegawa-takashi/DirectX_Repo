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
	// ---- Convert�e��
	void Conversion(TCHAR szstr[],short value);
	void Conversion(TCHAR szstr[],unsigned short value);
	void Conversion(TCHAR szstr[],int value);
	void Conversion(TCHAR szstr[],unsigned int value);
	void Conversion(TCHAR szstr[],float value);
	void Conversion(TCHAR szstr[],double value);
	void Conversion(TCHAR szstr[],bool value);
	void Conversion(TCHAR szstr[],D3DXVECTOR3 value);


private:
	

	LPD3DXFONT pFont; // �t�H���g�I�u�W�F�N�g
 	TCHAR Msg[256];	  // ���b�Z�[�W���e

#if _UNICODE
	std::wstring str;			// �f�o�b�O������ێ��o�b�t�@�iUNICODE�p�j
#else
	std::string str;				// �f�o�b�O������ێ��o�b�t�@�iANCI�p�j
#endif
};

