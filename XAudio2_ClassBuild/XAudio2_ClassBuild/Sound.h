#pragma once

namespace bgmdata {
	enum BgmNameList
	{
		Sound1,
		Sound2,
		MAX_BGM,
	};
	static char* BGMName[bgmdata::MAX_BGM] =
	{
		"../data/Sound/Bgm/test.wav",
		"../data/Sound/Bgm/test2.wav",
	};
}

#include<XAudio2.h>
#include<iostream>
#include<stdexcept>
#include<vorbis\codec.h>
#include<vorbis\vorbisfile.h>

#pragma comment(lib,"libogg_static.lib")
#pragma comment(lib,"libvorbis_static.lib")
#pragma comment(lib,"libvorbisfile_static.lib")