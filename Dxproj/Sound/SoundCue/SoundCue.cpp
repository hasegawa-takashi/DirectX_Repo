#include "SoundCue.h"



CSoundCue::CSoundCue()
{
}


CSoundCue::~CSoundCue()
{
	// ���X�g�̍폜
	for each (auto var in m_Voicelist)
	{
		delete var;
	}
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

	m_Voicelist.push_back(voice);
}

//-----------------------------------------------------------------
//
//	ChangeVolume
//		Cue�P�ʂł̉��ʂ̕ύX
//
void CSoundCue::ChangeVolume(float volume)
{
	m_CueVolume = volume;

	for (auto var = m_Voicelist.begin(); var != m_Voicelist.end(); ++var )
	{
		 (*var)->RegistVoice->SetVolume( (volume * (*var)->Soundelemt.MaxVolume) );
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
		// TODO :: ����{���ɓ����̂��낤���c�H
		if ( *(var._Ptr) == voice)
		{
			m_Voicelist.erase(var);
		}
	}
}