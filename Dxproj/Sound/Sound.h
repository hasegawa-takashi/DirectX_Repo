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

// �Œ�l�錾
#define BUFF_SIZE           6720
#define MAX_FREQ            22		//KHz

// �O���錾
class CLoadSoundFile;

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
	int PlayTime;
};


/**
Sourcevoice�̐ݒ�
*/
struct AudioElement
{
	SoundElement Soundelemt;				// �����t�@�C���̏��
	IXAudio2SourceVoice* RegistVoice;		// �o�^�����Source�{�C�X(�|�C���^�Q��<���̂�Component�Ŏ���>)
};


