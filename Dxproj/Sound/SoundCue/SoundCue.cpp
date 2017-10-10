#include "SoundCue.h"



CSoundCue::CSoundCue()
{
}


CSoundCue::~CSoundCue()
{
	// リストの削除
	for each (auto var in m_Voicelist)
	{
		delete var;
	}
	m_Voicelist.clear();
}


//-----------------------------------------------------------------
//
//	Registervoice
//		ソースボイスの登録
//
void CSoundCue::Registervoice(AudioElement* voice)
{
	(voice)->RegistVoice->SetVolume((voice)->Soundelemt.MaxVolume);

	m_Voicelist.push_back(voice);
}

//-----------------------------------------------------------------
//
//	ChangeVolume
//		Cue単位での音量の変更
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
//		ソースボイスの解除
//
void CSoundCue::UnRegistervoice(AudioElement* voice)
{
	for (auto var = m_Voicelist.begin(); var != m_Voicelist.end(); ++var)
	{
		// TODO :: これ本当に動くのだろうか…？
		if ( *(var._Ptr) == voice)
		{
			m_Voicelist.erase(var);
		}
	}
}