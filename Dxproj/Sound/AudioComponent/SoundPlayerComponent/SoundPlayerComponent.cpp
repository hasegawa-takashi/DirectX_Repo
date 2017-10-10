#include "SoundPlayerComponent.h"



CSoundPlayerComponent::CSoundPlayerComponent()
{

}

CSoundPlayerComponent::~CSoundPlayerComponent()
{
	// Voice�̍폜
	m_VoiceElement->RegistVoice->DestroyVoice();
	delete m_VoiceElement;


}

IXAudio2SourceVoice** CSoundPlayerComponent::Init(std::string type, std::string name)
{
	m_PlayNowFlag = false;

	// �{�C�X�G�������g�̍쐬
	m_VoiceElement = new AudioElement();

	// �{�����[��
	CAudioDatabase::Instance()->SetAudioSource( &m_VoiceElement, type, name);

	// XAudio2�o�b�t�@�̐ݒ�
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�[��
	buffer = m_VoiceElement->Soundelemt.Loadsoundfile->StreamloadBuffer();

	//
	m_VoiceElement->RegistVoice->SubmitSourceBuffer(&buffer);

	// �\�[�X�{�C�X�̂߂���[���ҁ[
	(m_Sourcevoice) = (m_VoiceElement->RegistVoice);
	
	// ����buffer���̎擾
	return &m_VoiceElement->RegistVoice;
}

// �X�V����
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

// �Đ�����
void CSoundPlayerComponent::Play()
{
	m_VoiceElement->RegistVoice->Start();

	m_PlayNowFlag = true;

}

// ��~����
void CSoundPlayerComponent::Stop()
{
	m_VoiceElement->RegistVoice->Stop();
}

// ���ʏ���
void CSoundPlayerComponent::ChangeVolume(float volume)
{
	m_VoiceElement->RegistVoice->SetVolume(volume);
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