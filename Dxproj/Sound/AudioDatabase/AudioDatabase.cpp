#include "AudioDatabase.h"


CAudioDatabase::CAudioDatabase()
{
}

// �I������
CAudioDatabase::~CAudioDatabase()
{
	DeleteSoundData();
	CloseResourceFile();
}

//-----------------------------------------------------------------
//
//	LoadResourceFile
//		���\�[�X�t�@�C���̃��[�h
//
void CAudioDatabase::LoadResourceFile(std::string name)
{
	// Csv�̓ǂݍ��݁B
	CWaveformatData* waveformatdata = new CWaveformatData(name);

	// �o�^������B
	m_Waveformat.insert( std::make_pair(name,waveformatdata) );
	
	// Cue�f�[�^�̍쐬
	CSoundCue* soundcue = new CSoundCue();
	m_Cuemap.insert( std::make_pair(name, soundcue) );

	

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

	// �SWavedata�̍폜
	for each (auto var in m_Cuemap)
	{
		delete var.second;
	}

	// Dictionary�̍폜
	m_Cuemap.clear();
}

//-----------------------------------------------------------------
//
//	CloseResourceFile
//		�ǂݍ��񂾃��\�[�X�t�H���_�̊J��
//
void CAudioDatabase::CloseResourceFile()
{
	if (m_Waveformat.empty())
		return;

	// �SWavedata�̍폜
	for each (auto var in m_Waveformat)
	{
		delete var.second;
	}

	// Dictionary�̍폜
	m_Waveformat.clear();

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
//
void CAudioDatabase::SetAudioSource(AudioElement** audioelement, std::string type ,std::string name)
{

	if (m_Waveformat.empty())
	{
		return;
	}

	// Wave���̎擾
	(*audioelement)->Soundelemt = m_Waveformat[type]->GetWaveElement(name);

	// �}�X�^�[�{�C�X�ւ̓o�^
	GetXAudio2Mgr()->SetXAudio2SourceVoice( &(*audioelement)->RegistVoice , *(*audioelement)->Soundelemt.Waveformat);

	// ��ނ��Ƃ�Source�{�C�X�̓o�^
	m_Cuemap[type]->Registervoice(*audioelement);
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

	m_Cuemap[name]->ChangeVolume(volume);
}