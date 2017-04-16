#include "BGM.h"

//==========================================================
//
//		CBGMŒn
//
//==========================================================
static const char* g_pszFileBGM[MAX_BGM] = {
	"test.mp3",
};

CBGM::CBGM()
{
	ReadWaveFile();
}

CBGM::~CBGM()
{

};

//////////////////////////////////////////////////////////////
//
//	WaveFile‚ðBGM‚Æ‚µ‚Ä“o˜^
//
void CBGM::ReadWaveFile()
{

	CLoadWave *wave;
	WAVEFORMATEX wavefmt;

	for (int loop = 0; loop < MAX_BGM; loop++)
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

		GetSoundMgr()->SetSourcevoice(m_Voice[loop], wavefmt);
	}
}

//////////////////////////////////////////////////////////////
//
//	Ä¶
//
void CBGM::PlayBGM(BGMList list)
{
	m_Voice[list]->Start();
}