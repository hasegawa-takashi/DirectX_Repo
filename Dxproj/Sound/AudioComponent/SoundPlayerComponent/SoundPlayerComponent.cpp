#include "SoundPlayerComponent.h"



CSoundPlayerComponent::CSoundPlayerComponent()
{

}

CSoundPlayerComponent::~CSoundPlayerComponent()
{
	// Voiceの削除
	m_VoiceElement->RegistVoice->DestroyVoice();
	delete m_VoiceElement;


}

IXAudio2SourceVoice** CSoundPlayerComponent::Init(std::string type, std::string name)
{
	m_PlayNowFlag = false;

	// ボイスエレメントの作成
	m_VoiceElement = new AudioElement();

	// ボリューム
	CAudioDatabase::Instance()->SetAudioSource( &m_VoiceElement, type, name);

	// XAudio2バッファの設定
	XAUDIO2_BUFFER buffer;

	// バッファーを
	buffer = m_VoiceElement->Soundelemt.Loadsoundfile->StreamloadBuffer();

	//
	m_VoiceElement->RegistVoice->SubmitSourceBuffer(&buffer);

	// ソースボイスのめもりーこぴー
	(m_Sourcevoice) = (m_VoiceElement->RegistVoice);
	
	// 現在buffer分の取得
	return &m_VoiceElement->RegistVoice;
}

// 更新処理
void CSoundPlayerComponent::ComponentUpdate()
{
	XAUDIO2_BUFFER buffer;

	buffer = m_VoiceElement->Soundelemt.Loadsoundfile->UpdateBuffer(m_Sourcevoice);

	if (buffer.AudioBytes != 0)
	{
		m_Sourcevoice->SubmitSourceBuffer(&buffer);
		m_VoiceElement->Soundelemt.PlayTime = 0;
	}

	if (m_PlayNowFlag)
	{
		m_VoiceElement->Soundelemt.PlayTime++;
	}

}

// 再生処理
void CSoundPlayerComponent::Play()
{
	m_VoiceElement->RegistVoice->Start();

	m_PlayNowFlag = true;

}

// 停止処理
void CSoundPlayerComponent::Stop()
{
	m_VoiceElement->RegistVoice->Stop();
}

// 音量処理
void CSoundPlayerComponent::ChangeVolume(float volume)
{
	m_VoiceElement->RegistVoice->SetVolume(volume);
}


//-----------------------------------------------------------------
//
//	GetSpectrumData
//		FFT計算した現在のbufferの数値
//
// TODO いまいちしっかり数値取れてないので放置、どうしようこれ
bool CSoundPlayerComponent::GetSpectrumData()
{
	// バッファの更新確認
	if( (m_VoiceElement->Soundelemt.Loadsoundfile->GetNextbufferTime(m_Sourcevoice) == false ) )
	{
		return false;
	}

	std::vector<float> samplebuffer;
	samplebuffer = m_VoiceElement->Soundelemt.Loadsoundfile->GetPrimaryBuffer();

	
	CalcFreq( BUFF_SIZE * 2, m_VoiceElement->Soundelemt.Waveformat->nSamplesPerSec);

	

	return true;

}

//-----------------------------------------------------------------
//
//	CalcFreq
//		FFTWの計算
//
void CSoundPlayerComponent::CalcFreq( size_t len, int Fs)
{
	//for (int i = 0; i < len; i++) {
	//	int re, im;
	//	float freq, magnitude;
	//	int index;

	//	 複素数配列に入力データをセット
	//	re = m_fftwcompOut[i][0];
	//	im = m_fftwcompOut[i][1];
	//	
	//	magnitude = sqrt(re * re + im * im);
	//	freq = i * Fs / len;
	//			
	//	index = freq / 1000;//round(freq);

	//	if (index <= MAX_FREQ) {
	//		m_freqMagnitude[index] += magnitude;			
	//	}
	//}
}