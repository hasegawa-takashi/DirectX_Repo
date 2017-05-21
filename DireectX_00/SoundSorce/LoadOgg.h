#pragma once

#include<Windows.h>
#include<stdexcept>
#include<vorbis\codec.h>
#include<vorbis\vorbisfile.h>

#pragma comment(lib,"libogg_static.lib")
#pragma comment(lib,"libvorbid_static.lib")
#pragma comment(lib,"libvorbidfile_static.lib")

//=================================================================
//
//	ogg�t�@�C���̓ǂݍ��ݗp
//	
//	�X�g���[�~���O�@�\���Ȃ��̂Ō�X�����\��
//
//=================================================================
class CLoadOgg
{
public:
	CLoadOgg();
	~CLoadOgg();

	void LoadOggFile(char* filename);
	WAVEFORMATEX* GetWaveFormat();


private:
	OggVorbis_File m_ovf;
	WAVEFORMATEX m_waveformat;
};

