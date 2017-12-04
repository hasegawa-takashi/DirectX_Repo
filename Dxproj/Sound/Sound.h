#pragma once

#include<d3dx9.h>
#include<XAudio2.h>
#include<X3DAudio.h>
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
#include<memory>
#include<complex>

#pragma comment(lib,"X3daudio.lib")
#pragma comment(lib,"../data/Lib/libvorbisfile_static.lib")
#pragma comment(lib,"../data/Lib/libogg_static.lib")
#pragma comment(lib,"../data/Lib/libvorbis_static.lib")

#include"vorbis/vorbisfile.h"

#define _USE_VOICECALLBACK_
// 固定値宣言
#define BUFF_SIZE           4096
#define MAX_FREQ            22		//KHz

// 前方宣言
class CLoadSoundFile;
class CWaveformatData;

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
	int PlayTime = 0;
};


/**
Sourcevoiceの設定
*/
struct AudioElement
{
	SoundElement Soundelemt;				// 音声ファイルの情報
	IXAudio2SourceVoice* RegistVoice;		// 登録されるSourceボイス(ポインタ参照<実体はComponentで持つ>)
	CWaveformatData* Waveformatdata;		// 読み込んだ外部リソースデータ
};


class VoiceCallback : public IXAudio2VoiceCallback {
public:
	HANDLE g_hEvent = NULL;
	VoiceCallback():g_hEvent(CreateEvent(NULL, FALSE, FALSE, NULL) ) { }
	~VoiceCallback() { CloseHandle(g_hEvent); }

	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 BytesRequired) { }
	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd(void) { }
	void STDMETHODCALLTYPE OnStreamEnd(void) { SetEvent(g_hEvent); }
	void STDMETHODCALLTYPE OnBufferStart(void *pBufferContext) { SetEvent(g_hEvent); }
	void STDMETHODCALLTYPE OnBufferEnd(void *pBufferContext) { }
	void STDMETHODCALLTYPE OnLoopEnd(void *pBufferContext) { }
	void STDMETHODCALLTYPE OnVoiceError(void *pBufferContext, HRESULT Error) { }
};