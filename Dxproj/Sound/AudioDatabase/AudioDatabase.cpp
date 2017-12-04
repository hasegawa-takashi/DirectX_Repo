#include "AudioDatabase.h"


CAudioDatabase::CAudioDatabase()
{
}

// �I������
CAudioDatabase::~CAudioDatabase()
{
	DeleteSoundData();
}

//-----------------------------------------------------------------
//
//	LoadResourceFile
//		���\�[�X�t�@�C���̃��[�h
//
void CAudioDatabase::SetVoiceCue(std::string name, AudioElement* voice)
{
	// Cue�f�[�^�̍쐬
	CSoundCue soundcue;
	soundcue.Registervoice(voice);
	m_Cuemap.insert( std::make_pair(name, soundcue) );
}

void CAudioDatabase::PopVoiceCue(std::string name, AudioElement* voice)
{
	// Cue�f�[�^�̍쐬
	m_Cuemap[name].UnRegistervoice(voice);
}

//-----------------------------------------------------------------
//
//	DeleteSoundData
//		�ێ����Ă���SourceVoice�̍폜
//
void CAudioDatabase::DeleteSoundData()
{

	if (m_Cuemap.empty())
		return;

	// Dictionary�̍폜
	m_Cuemap.clear();
}

//-----------------------------------------------------------------
//
//	SetListener
//		���X�i�[�̓o�^
//
void CAudioDatabase::SetListener(D3DXMATRIX* listener)
{
	CX3DSound::Instance()->SetListener(listener);
}

//-----------------------------------------------------------------
//
//	SetAudioSource
//		�Đ������̓o�^
//		�����Ő������������e��|�C���^�Ɏ������čĐ���������		
//		Bug :: �����ł̃R�s�[���������Ă��Ȃ����߂ɓ����ɉ�����ƃo�O���������Ă���\��
//
void CAudioDatabase::SetAudioSource(AudioElement* audioelement, std::string type ,std::string name, VoiceCallback* voiceCallback)
{
	// Wave�����O�����[�X����ǂݍ���Ŏ擾
	audioelement->Waveformatdata = new CWaveformatData(type,name);
	audioelement->Soundelemt = audioelement->Waveformatdata->GetWaveElement();

	// �}�X�^�[�{�C�X�ւ̓o�^
	GetXAudio2Mgr()->SetXAudio2SourceVoice( &(audioelement)->RegistVoice , *(audioelement)->Soundelemt.Waveformat, voiceCallback);

	// ��ޕʂɓo�^
	m_Cuemap[type].Registervoice(audioelement);

	// ���ʂ̐ݒ�
	(audioelement)->RegistVoice->SetVolume(audioelement->Soundelemt.MaxVolume);
}

//-----------------------------------------------------------------
//
//	ChangeVolume
//		��ނ��Ƃ̃{�����[���̕ύX
//
void CAudioDatabase::ChangeCueVolume(std::string name, float volume)
{
	if (m_Cuemap.empty())
		return;

	m_Cuemap[name].ChangeVolume(volume);
}