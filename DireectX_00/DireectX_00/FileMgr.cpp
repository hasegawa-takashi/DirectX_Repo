#include "FileMgr.h"


FileMgr::FileMgr()
{
}


FileMgr::~FileMgr()
{
}

bool FileMgr::FileRead(BulletBox *box , char *FilePath)
{
	// string�^�ϊ�
	std::string filename = FilePath;
	// �t�@�C���̃I�[�v��
	ifs.open(FilePath,std::ios::in);

	/*while (!ifs.eof())
	{

	}*/

	return true;

}