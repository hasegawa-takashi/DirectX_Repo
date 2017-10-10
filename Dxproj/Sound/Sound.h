#pragma once

#include<d3dx9.h>
#include<iostream>
#include<stdexcept>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include<memory>
#include<functional>
#include<XDSP.h>

#include<complex>

#include"../includeheader.h"

// 固定値宣言
#define BUFF_SIZE           6720
#define MAX_FREQ            22		//KHz

// 前方宣言
class CLoadSoundFile;

// 構造体
//==================================================
//
//	Wsaveファイルのフォーマット
//
//==================================================
struct SoundElement
{
	CLoadSoundFile* Loadsoundfile;	// ロードされたファイルデータ
	WAVEFORMATEX* Waveformat;		// Chunkdata
	std::string Audiotype;			// 種類(Bgm : Se : Voice など)
	std::string FileName;			// ファイル名
	std::string Resourcetype;		// 拡張子(.wav : .ogg)
	bool Loop;						// ループ再生フラグ
	int StreamType;					// 0 Preload : 1 Stream
	float MaxVolume;				// 1サウンドの最大音量(1.0f ~ 0.0f)
	int PlayTime;
};


/**
Sourcevoiceの設定
*/
struct AudioElement
{
	SoundElement Soundelemt;				// 音声ファイルの情報
	IXAudio2SourceVoice* RegistVoice;		// 登録されるSourceボイス(ポインタ参照<実体はComponentで持つ>)
};


