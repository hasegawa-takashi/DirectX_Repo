#pragma once
#include<iostream>
#include<fstream>
// 外部ファイル読み込み用インクルード
#include"Ballet.h"

class FileMgr
{
public:
	FileMgr();
	~FileMgr();

	bool FileRead(BulletBox *box,char *FilePath);

private:
	std::ifstream ifs;

};

