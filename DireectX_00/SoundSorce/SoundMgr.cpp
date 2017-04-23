#include "SoundMgr.h"



CSoundMgr::CSoundMgr()
{
	m_XAudiointerface = new CXAudio2Interface();
	m_Bgmdata = new CBgmDatabase();

}


CSoundMgr::~CSoundMgr()
{
}

void CSoundMgr::Play(bgmdata::BgmNameList name)
{

	m_Bgmdata->Play(name);

}

void CSoundMgr::Update()
{
	m_Bgmdata->BufferUpdate();
}

bool CSoundMgr::SetXAudio2Souce(IXAudio2SourceVoice** s, WAVEFORMATEX* w)
{
	return m_XAudiointerface->SetXAudio2SouceVoice(s,w);
}