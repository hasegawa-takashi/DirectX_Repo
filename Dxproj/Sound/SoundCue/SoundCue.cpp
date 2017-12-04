#include "SoundCue.h"



CSoundCue::CSoundCue()
{
	m_CueVolume = 1.0f;
	m_CueMute = false; 
}


CSoundCue::~CSoundCue()
{
	// ���X�g�̍폜
	if (m_Voicelist.empty())
		return;

	m_Voicelist.clear();
}


//-----------------------------------------------------------------
//
//	Registervoice
//		�\�[�X�{�C�X�̓o�^
//
void CSoundCue::Registervoice(AudioElement* voice)
{
	(voice)->RegistVoice->SetVolume((voice)->Soundelemt.MaxVolume);

	m_Voicelist.push_back( voice );
}

//-----------------------------------------------------------------
//
//	ChangeVolume
//		Cue�P�ʂł̉��ʂ̕ύX
//
void CSoundCue::ChangeVolume(float volume)
{
	if (volume > 1.0f)
	{
		volume = 1.0f;
	}
	if (volume < 0.0f)
	{
		volume = 0.0f;
	}

	if (m_CueVolume == volume)
	{
		return;
	}


	m_CueVolume = volume;
	

	for (auto var = m_Voicelist.begin(); var != m_Voicelist.end(); ++var )
	{
		float setvol = (volume * (*var)->Soundelemt.MaxVolume);
		(*var)->RegistVoice->SetVolume(setvol);
	}

}

//-----------------------------------------------------------------
//
//	UnRegistervoice
//		�\�[�X�{�C�X�̉���
//
void CSoundCue::UnRegistervoice(AudioElement* voice)
{
	for (auto var = m_Voicelist.begin(); var != m_Voicelist.end(); ++var)
	{
		if ( *(var) == voice)
		{
			m_Voicelist.erase(var);
			break;
		}
	}
}