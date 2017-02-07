#include "FileMgr.h"


FileMgr::FileMgr()
{
}


FileMgr::~FileMgr()
{
}

bool FileMgr::FileRead(BulletBox *box , char *FilePath)
{
	// string型変換
	std::string filename = FilePath;
	// ファイルのオープン
	ifs.open(FilePath,std::ios::in);

	/*while (!ifs.eof())
	{

	}*/

	return true;

}