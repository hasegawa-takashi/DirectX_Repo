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
	m_Reverbpram.RoomSize  = FXREVERB_MIN_ROOMSIZE;

	// �G�R�[�̏�����
	m_EchoPram.Delay		= FXECHO_MIN_DELAY;
	m_EchoPram.Feedback		= FXECHO_MIN_FEEDBACK;
	m_EchoPram.WetDryMix	= FXECHO_MIN_WETDRYMIX;

	// �C�R���C�U�̏�����
	// �C�R���C�U�̏�����
	m_EqPram.FrequencyCenter0 = FXEQ_DEFAULT_FREQUENCY_CENTER_0;
	m_EqPram.FrequencyCenter1 = FXEQ_DEFAULT_FREQUENCY_CENTER_1;
	m_EqPram.FrequencyCenter2 = FXEQ_DEFAULT_FREQUENCY_CENTER_2;
	m_EqPram.FrequencyCenter3 = FXEQ_DEFAULT_FREQUENCY_CENTER_3;
	m_EqPram.Gain0 = FXEQ_DEFAULT_GAIN;
	m_EqPram.Gain1 = FXEQ_DEFAULT_GAIN;
	m_EqPram.Gain2 = FXEQ_DEFAULT_GAIN;
	m_EqPram.Gain3 = FXEQ_DEFAULT_GAIN;
	m_EqPram.Bandwidth0 = FXEQ_DEFAULT_BANDWIDTH;
	m_EqPram.Bandwidth1 = FXEQ_DEFAULT_BANDWIDTH;
	m_EqPram.Bandwidth2 = FXEQ_DEFAULT_BANDWIDTH;
	m_EqPram.Bandwidth3 = FXEQ_DEFAULT_BANDWIDTH;

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
	m_Reverbpram.Diffusion = walltype;
	m_Reverbpram.RoomSize = roomsize;

	m_voice->SetEffectParameters(0, &m_Reverbpram, sizeof(FXREVERB_PARAMETERS));
}

//-----------------------------------------------------------------
//
//	offsetReverbVolume
//		Reverb�̒l�̃��Z�b�g
//
void CSoundEffectComponent::offsetReverbVolume()
{
	m_Reverbpram.Diffusion = FXREVERB_MIN_DIFFUSION;
	m_Reverbpram.RoomSize = FXREVERB_MIN_ROOMSIZE;
	
	m_voice->SetEffectParameters(0, &m_Reverbpram, sizeof(FXREVERB_PARAMETERS));
}

//-----------------------------------------------------------------
//
//	SetEchoVolume
//		�G�R�[�̒l�̕ύX
//
void CSoundEffectComponent::SetEchoVolume(float Delay, float feedback, float wetdry)
{
	m_EchoPram.Delay = Delay;
	m_EchoPram.Feedback = feedback;
	m_EchoPram.WetDryMix = wetdry;

	m_voice->SetEffectParameters(1, &m_EchoPram, sizeof(FXECHO_PARAMETERS));
}

//-----------------------------------------------------------------
//
//	offsetEchoVolume
//		Echo�̒l�̃��Z�b�g
//
void CSoundEffectComponent::offsetEchoVolume()
{
	m_EchoPram.Delay = FXECHO_MIN_DELAY;
	m_EchoPram.Feedback = FXECHO_MIN_FEEDBACK;
	m_EchoPram.WetDryMix = FXECHO_MIN_WETDRYMIX;

	m_voice->SetEffectParameters(1, &m_EchoPram, sizeof(FXECHO_PARAMETERS));
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
//	offsetPitchRate
//		Pitch�̒l�̃��Z�b�g
//
void  CSoundEffectComponent::offsetPitchRate()
{
	m_voice->SetFrequencyRatio(1.0f);
}

//-----------------------------------------------------------------
//
//	SetEQVolume
//		EQ�̒l�̐ݒ�
//
void CSoundEffectComponent::SetEQVolume(float freqcenter[4],float gain[4],float bandwidth[4])
{
	m_EqPram.FrequencyCenter0 = FXEQ_DEFAULT_FREQUENCY_CENTER_0;
	m_EqPram.FrequencyCenter1 = FXEQ_DEFAULT_FREQUENCY_CENTER_1;
	m_EqPram.FrequencyCenter2 = FXEQ_DEFAULT_FREQUENCY_CENTER_2;
	m_EqPram.FrequencyCenter3 = FXEQ_DEFAULT_FREQUENCY_CENTER_3;
	m_EqPram.Gain0 = gain[0];
	m_EqPram.Gain1 = gain[1];
	m_EqPram.Gain2 = gain[2];
	m_EqPram.Gain3 = gain[3];
	m_EqPram.Bandwidth0 = FXEQ_DEFAULT_BANDWIDTH;
	m_EqPram.Bandwidth1 = FXEQ_DEFAULT_BANDWIDTH;
	m_EqPram.Bandwidth2 = FXEQ_DEFAULT_BANDWIDTH;
	m_EqPram.Bandwidth3 = FXEQ_DEFAULT_BANDWIDTH;

	m_voice->SetEffectParameters(2, &m_EqPram, sizeof(FXEQ_PARAMETERS));
}

//-----------------------------------------------------------------
//
//	offSetEQVolume
//		EQ�̒l�̃��Z�b�g
//
void CSoundEffectComponent::offSetEQVolume()
{
	m_EqPram.FrequencyCenter0 = FXEQ_DEFAULT_FREQUENCY_CENTER_0;
	m_EqPram.FrequencyCenter1 = FXEQ_DEFAULT_FREQUENCY_CENTER_1;
	m_EqPram.FrequencyCenter2 = FXEQ_DEFAULT_FREQUENCY_CENTER_2;
	m_EqPram.FrequencyCenter3 = FXEQ_DEFAULT_FREQUENCY_CENTER_3;
	m_EqPram.Gain0 = FXEQ_DEFAULT_GAIN;
	m_EqPram.Gain1 = FXEQ_DEFAULT_GAIN;
	m_EqPram.Gain2 = FXEQ_DEFAULT_GAIN;
	m_EqPram.Gain3 = FXEQ_DEFAULT_GAIN;
	m_EqPram.Bandwidth0 = FXEQ_DEFAULT_BANDWIDTH;
	m_EqPram.Bandwidth1 = FXEQ_DEFAULT_BANDWIDTH;
	m_EqPram.Bandwidth2 = FXEQ_DEFAULT_BANDWIDTH;
	m_EqPram.Bandwidth3 = FXEQ_DEFAULT_BANDWIDTH;

	m_voice->SetEffectParameters(2, &m_EqPram, sizeof(FXEQ_PARAMETERS));
}

void CSoundEffectComponent::SetSpaceEffect()
{
	m_EchoPram.Delay = m_SpaceDlay;
	m_EchoPram.Feedback = m_SpaceFeedback;
	m_EchoPram.WetDryMix = m_SpaceDlywet;

	m_voice->SetEffectParameters(1, &m_EchoPram, sizeof(FXECHO_PARAMETERS));
}

void CSoundEffectComponent::offsetSpaceEffect()
{
	offsetEchoVolume();
}

void CSoundEffectComponent::SetTunnelEffect()
{
	m_Reverbpram.Diffusion = m_TunnelWall;
	m_Reverbpram.RoomSize = m_TunnelRoomsize;

	m_voice->SetEffectParameters(0, &m_Reverbpram, sizeof(FXREVERB_PARAMETERS));
}

void CSoundEffectComponent::offsetTunnelEffect()
{
	offsetReverbVolume();
}