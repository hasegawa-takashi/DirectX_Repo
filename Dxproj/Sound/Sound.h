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
// �Œ�l�錾
#define BUFF_SIZE           4096
#define MAX_FREQ            22		//KHz

// �O���錾
class CLoadSoundFile;
class CWaveformatData;

// �\����
//==================================================
//
//	Wsave�t�@�C���̃t�H�[�}�b�g
//
//==================================================
struct SoundElement
{
	CLoadSoundFile* Loadsoundfile;	// ���[�h���ꂽ�t�@�C���f�[�^
	WAVEFORMATEX* Waveformat;		// Chunkdata
	std::string Audiotype;			// ���(Bgm : Se : Voice �Ȃ�)
	std::string FileName;			// �t�@�C����
	std::string Resourcetype;		// �g���q(.wav : .ogg)
	bool Loop;						// ���[�v�Đ��t���O
	int StreamType;					// 0 Preload : 1 Stream
	float MaxVolume;				// 1�T�E���h�̍ő剹��(1.0f ~ 0.0f)
	int PlayTime = 0;
};


/**
Sourcevoice�̐ݒ�
*/
struct AudioElement
{
	SoundElement Soundelemt;				// �����t�@�C���̏��
	IXAudio2SourceVoice* RegistVoice;		// �o�^�����Source�{�C�X(�|�C���^�Q��<���̂�Component�Ŏ���>)
	CWaveformatData* Waveformatdata;		// �ǂݍ��񂾊O�����\�[�X�f�[�^
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