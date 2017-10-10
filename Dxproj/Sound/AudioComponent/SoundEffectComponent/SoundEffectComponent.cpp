#include "SoundEffectComponent.h"

//-----------------------------------------------------------------
//
//	CSoundEffectComponent
//		XAPOFX�̏�����
//
CSoundEffectComponent::CSoundEffectComponent()
{
	
}

CSoundEffectComponent::~CSoundEffectComponent()
{
}

void CSoundEffectComponent::ComponentUpdate()
{

}


void CSoundEffectComponent::Init(IXAudio2SourceVoice* voice)
{
	m_voice = voice;

	// �e��̐ݒ�
	CreateFX(__uuidof(::FXReverb), &m_Effect[0]);
	CreateFX(__uuidof(::FXEcho), &m_Effect[1]);
	CreateFX(__uuidof(::FXEQ), &m_Effect[2]);

	m_desc[0].InitialState = TRUE;
	m_desc[0].OutputChannels = 2;
	m_desc[0].pEffect = m_Effect[0];

	m_desc[1].InitialState = TRUE;
	m_desc[1].OutputChannels = 2;
	m_desc[1].pEffect = m_Effect[1];

	m_desc[2].InitialState = TRUE;
	m_desc[2].OutputChannels = 2;
	m_desc[2].pEffect = m_Effect[2];

	m_chain.pEffectDescriptors = m_desc;
	m_chain.EffectCount = 3;

	m_voice->SetEffectChain(&m_chain);

	// ���o�[�u�̏�����
	m_Reverbpram.Diffusion = FXREVERB_MIN_DIFFUSION;
	m_Reverbpram.RoomSize = FXREVERB_MIN_ROOMSIZE;

	// �G�R�[�̏�����
	m_EchoPram.Delay = FXECHO_MIN_DELAY;
	m_EchoPram.Feedback = FXECHO_MIN_FEEDBACK;
	m_EchoPram.WetDryMix = FXECHO_MIN_WETDRYMIX;

	// �C�R���C�U�̏�����
	m_EqPram.FrequencyCenter0 = FXEQ_DEFAULT_FREQUENCY_CENTER_0;
	m_EqPram.FrequencyCenter1 = FXEQ_DEFAULT_FREQUENCY_CENTER_1;
	m_EqPram.FrequencyCenter2 = FXEQ_DEFAULT_FREQUENCY_CENTER_2;
	m_EqPram.FrequencyCenter3 = FXEQ_DEFAULT_FREQUENCY_CENTER_3;

	m_voice->SetEffectParameters(0, &m_Reverbpram, sizeof(FXREVERB_PARAMETERS));
	m_voice->SetEffectParameters(1, &m_EchoPram, sizeof(FXECHO_PARAMETERS));
	m_voice->SetEffectParameters(2, &m_EqPram, sizeof(FXEQ_PARAMETERS));

	// �q����̍폜
	for (int loop = 0; loop < XAPOFX_EFFECT_TYPE; ++loop)
	{
		m_Effect[loop]->Release();
	}
}

//-----------------------------------------------------------------
//
//	SetReverbVolume
//		Reverb�̒l�̕ύX
//
void CSoundEffectComponent::SetReverbVolume(float walltype, float roomsize)
{
	FXREVERB_PARAMETERS param;

	param.Diffusion = walltype;
	param.RoomSize = roomsize;

	m_voice->SetEffectParameters(0, &param, sizeof(FXREVERB_PARAMETERS));
}

//-----------------------------------------------------------------
//
//	offsetReverbVolume
//		Reverb�̒l�̃��Z�b�g
//
void CSoundEffectComponent::offsetReverbVolume()
{
	FXREVERB_PARAMETERS param;

	param.Diffusion = FXREVERB_MIN_DIFFUSION;
	param.RoomSize = FXREVERB_MIN_ROOMSIZE;

	m_voice->SetEffectParameters(0, &param, sizeof(FXREVERB_PARAMETERS));
}

//-----------------------------------------------------------------
//
//	SetEchoVolume
//		�G�R�[�̒l�̕ύX
//
void CSoundEffectComponent::SetEchoVolume(float Delay, float feedback, float wetdry)
{
	FXECHO_PARAMETERS param;

	param.Delay = Delay;
	param.Feedback = feedback;
	param.WetDryMix = wetdry;

	m_voice->SetEffectParameters(1, &param, sizeof(FXECHO_PARAMETERS));
}

//-----------------------------------------------------------------
//
//	offsetEchoVolume
//		Echo�̒l�̃��Z�b�g
//
void CSoundEffectComponent::offsetEchoVolume()
{
	FXECHO_PARAMETERS param;

	param.Delay = FXECHO_MIN_DELAY;
	param.Feedback = FXECHO_MIN_FEEDBACK;
	param.WetDryMix = FXECHO_MIN_WETDRYMIX;

	m_voice->SetEffectParameters(1, &param, sizeof(FXECHO_PARAMETERS));
}

//-----------------------------------------------------------------
//
//	SetPitchRate
//		Pitch�̒l�̕ύX
//
void  CSoundEffectComponent::SetPitchRate(float PitchRate)
{
	m_voice->SetFrequencyRatio(PitchRate);
}

//-----------------------------------------------------------------
//
//	SetPitchRate
//		Pitch�̒l�̃��Z�b�g
//
void  CSoundEffectComponent::offsetPitchRate()
{
	m_voice->SetFrequencyRatio(1.0f);
}