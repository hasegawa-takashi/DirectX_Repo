#pragma once
#include<iostream>
#include<fstream>
// �O���t�@�C���ǂݍ��ݗp�C���N���[�h
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

