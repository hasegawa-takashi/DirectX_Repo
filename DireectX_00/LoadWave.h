#pragma once


/*
‚±‚±Œ©‚Ü‚µ‚½
http://qiita.com/tobira-code/items/39936c4e2b1168fb79ce
*/

#include<XAudio2.h>
#include <mmsystem.h>
#include<tchar.h>

namespace BGMList
{
	enum {
		Title,
		MAX_BGM
	};
}

static const LPSTR g_pszFileBGM[BGMList::MAX_BGM] = {
	_T("../data/Sound/Bgm/test.wav")
};


class CLoadWave
{
public:
	CLoadWave();
	~CLoadWave();

private:
	void OpenWave();
	HMMIO mmio[BGMList::MAX_BGM];
	MMRESULT mret[BGMList::MAX_BGM];

};

