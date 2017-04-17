#include "BGM.h"

//==========================================================
//
//		CBGMån
//
//==========================================================
static const char* g_pszFileBGM[BGMList::MAX_BGM] = {
	"../data/Sound/Bgm/HeroesofWarcraft.wav"
};

CBGM::CBGM()
{
	ReadWaveFile();
}

CBGM::~CBGM()
{
	Close();
};

//////////////////////////////////////////////////////////////
//
//	WaveFileÇBGMÇ∆ÇµÇƒìoò^
//
void CBGM::ReadWaveFile()
{

	CLoadWave *wave;
	WAVEFORMATEX wavefmt;

	for (int loop = 0; loop < BGMList::MAX_BGM; loop++)
	{
		wave = new CLoadWave(g_pszFileBGM[loop]);
		waveHeader header = wave->GetWaveDat();

		wavefmt.wFormatTag = WAVE_FORMAT_PCM;
		wavefmt.nChannels = header.fmt.Channel;
		wavefmt.nSamplesPerSec = header.fmt.samplingrate;
		wavefmt.nAvgBytesPerSec = wavefmt.nSamplesPerSec * wavefmt.nChannels / 8;
		wavefmt.wBitsPerSample = header.fmt.bit_depth;
		wavefmt.nBlockAlign = wavefmt.nChannels * wavefmt.wBitsPerSample / 8;
		wavefmt.cbSize = 0;

		GetSoundMgr()->SetSourcevoice(&m_Voice[loop], &wavefmt);
		m_Voice[loop]->SubmitSourceBuffer(&buffer);
	}
}

//////////////////////////////////////////////////////////////
//	çƒê∂
void CBGM::PlayBGM(int bgmlist)
{
	HRESULT hr =  m_Voice[bgmlist]->Start();

	if (FAILED(hr))
	{
		int i = 0;
	}
}

//////////////////////////////////////////////////////////////
//	BGMâπó ÇÃê›íË
void CBGM::SetBGMVol(float vol)
{
	for (int i = 0; i < BGMList::MAX_BGM; i++)
	{
		m_Voice[i]->SetVolume(vol);
	}

	Volume = vol;
}

//////////////////////////////////////////////////////////////
//	BGMâπó ÇÃéÊìæ
float CBGM::GetBGMVol()
{
	return Volume;
}

//////////////////////////////////////////////////////////////
//	BGMÇÃå„énññ
void CBGM::Close()
{
	for (int i = 0; i < BGMList::MAX_BGM; i++)
	{
		m_Voice[i]->DestroyVoice();
	}
}