#include "SoundPlayerComponent.h"

CSoundPlayerComponent::CSoundPlayerComponent()
	: m_VoiceElement(nullptr)
{
	m_Sourcevoice = nullptr;
	m_StartSamplePoint = { 0 };
	m_EndSamplePoint = { 0 };
	m_VoiceCallback = new VoiceCallback();
	m_VoiceCallback->OnStreamEnd();
	m_Fadefunc = nullptr;
}

CSoundPlayerComponent::~CSoundPlayerComponent()
{
	CAudioDatabase::Instance()->PopVoiceCue(m_VoiceElement->Soundelemt.Audiotype,m_VoiceElement);

	if (m_Sourcevoice != 0)
	{
		m_Sourcevoice->SetVolume(1.0f);
		m_Sourcevoice->Stop();
		m_Sourcevoice->DestroyVoice();
	}

	if (m_VoiceElement->Waveformatdata != nullptr)
	{
		delete m_VoiceElement->Waveformatdata;
	}

	
	delete m_VoiceCallback;
	delete m_VoiceElement;

	m_VoiceElement = nullptr;
	m_VoiceCallback = nullptr;
	m_Fadefunc.~function();
}

bool CSoundPlayerComponent::EndSoundflag()
{
	if (WAIT_OBJECT_0 == WaitForSingleObject(m_VoiceCallback->g_hEvent, INFINITE))
	{
		return true;
	}

	return false;
}

IXAudio2SourceVoice** CSoundPlayerComponent::Init(std::string type, std::string name)
{
	m_PlayNowFlag = false;

	// �{�C�X�G�������g�̍쐬
	m_VoiceElement = new AudioElement();
	
	// 
	CAudioDatabase::Instance()->SetAudioSource( m_VoiceElement, type, name,m_VoiceCallback);
	
	switch (m_VoiceElement->Soundelemt.StreamType)
	{

	case 0:
		m_Buffer = m_VoiceElement->Soundelemt.Loadsoundfile->PreloadBuffer(m_StartSamplePoint, m_EndSamplePoint);
		break;

	case 1:
		m_Buffer = m_VoiceElement->Soundelemt.Loadsoundfile->StreamloadBuffer();
		break;

	default:
		break;
	}

	// �\�[�X�{�C�X�̂߂���[���ҁ[
	m_Sourcevoice = m_VoiceElement->RegistVoice;

	// Sourcevoice�փo�b�t�@�̕ۑ�
	if (S_FALSE == m_Sourcevoice->SubmitSourceBuffer(&m_Buffer))
	{
		OutputDebugStringA("NG_Submitsource\n");
	}

	
	// ����buffer���̎擾
	return &m_Sourcevoice;
}

void CSoundPlayerComponent::FadePlay(int fadeSpd)
{
	m_Fadenum = 0;
	m_FadeSpd = fadeSpd;
	m_Sourcevoice->Start();
	m_PlayNowFlag = true;
	m_Fadefunc = std::bind(&CSoundPlayerComponent::FadeInPlay, this);
}

void CSoundPlayerComponent::FadeInPlay()
{
	float nowvol = 0;
	nowvol += m_FadeSpd*0.01f;
	// Fade�I��
	if (nowvol >= m_VoiceElement->Soundelemt.MaxVolume)
	{
		m_FadeSpd = 0;
		m_Fadefunc = nullptr;
		nowvol = m_VoiceElement->Soundelemt.MaxVolume;
	}

	HRESULT hr = m_Sourcevoice->SetVolume(nowvol);


}

/// <summary>
/// DestroyVoice�ŃG���[��f���Ă��܂����ߏ����ȃt�F�[�h�������������Ƃ�
/// </summary>
/// <param name="fadeSpd"></param>
void CSoundPlayerComponent::FadeStop(int fadeSpd)
{
	m_FadeSpd = fadeSpd;
	m_Fadenum = GetVolume();
	m_Fadefunc = std::bind(&CSoundPlayerComponent::FadeOutStop, this);
}

/// <summary>
/// �X�V�����̖{��
/// </summary>
/// <param name="fadespd"></param>
/// <returns></returns>
void CSoundPlayerComponent::FadeOutStop()
{
	float nowvol = 0.0f;
	nowvol = GetVolume();
	nowvol -= (m_FadeSpd* 0.01f);
		
	// Fade�I��
	if ( nowvol <= 0)
	{
		nowvol = 0;
		m_PlayNowFlag = false;
		m_FadeSpd = 0;
		m_Fadefunc = nullptr;
		m_Sourcevoice->SetVolume(0.0f);
		m_Sourcevoice->Stop();
	}

	HRESULT hr = m_Sourcevoice->SetVolume(nowvol);

}

// �X�V����
void CSoundPlayerComponent::ComponentUpdate()
{
	if (m_Fadefunc != nullptr)
	{	
		m_Fadefunc();
	}

	if (m_VoiceElement->Soundelemt.StreamType == 0)
	{
		return;
	}

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

// �Đ�����
void CSoundPlayerComponent::Play()
{
	if (m_PlayNowFlag)
	{
		return;
	}
	m_Sourcevoice->SetVolume(m_VoiceElement->Soundelemt.MaxVolume);

	HRESULT hr;
	hr = m_Sourcevoice->Start();

	if (hr == S_OK)
	{
		m_PlayNowFlag = true;
		return;
	}

	m_PlayNowFlag = false;
	
}

// ��~����
void CSoundPlayerComponent::Stop()
{
	m_Sourcevoice->Stop();
	m_PlayNowFlag = false;
}

// ���ʏ���
void CSoundPlayerComponent::ChangeVolume(float volume)
{
	m_Sourcevoice->SetVolume(volume);
}

float CSoundPlayerComponent::GetVolume()
{
	float vol;
	m_Sourcevoice->GetVolume(&vol);
	return vol;
}

//-----------------------------------------------------------------
//
//	GetSpectrumData
//		FFT�v�Z�������݂�buffer�̐��l
//
// TODO ���܂����������萔�l���ĂȂ��̂ŕ��u�A�ǂ����悤����
bool CSoundPlayerComponent::GetSpectrumData()
{
	// �o�b�t�@�̍X�V�m�F
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
//		FFTW�̌v�Z
//
void CSoundPlayerComponent::CalcFreq( size_t len, int Fs)
{
	//for (int i = 0; i < len; i++) {
	//	int re, im;
	//	float freq, magnitude;
	//	int index;

	//	 ���f���z��ɓ��̓f�[�^���Z�b�g
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