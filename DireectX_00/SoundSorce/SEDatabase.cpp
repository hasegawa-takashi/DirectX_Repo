#include "SEDatabase.h"

///////////////////////////////////////////////////////////
//
//	����
//
CSEDatabase::CSEDatabase()
{
	CreateSourceVoice();
	CreateVoiceEffect();

	Volume = 1.0f;

}

///////////////////////////////////////////////////////////
//
//	��������
//
CSEDatabase::~CSEDatabase()
{
	Close();
}

///////////////////////////////////////////////////////////
//
//	�\�[�X�{�C�X�̂����Ă�
//
void CSEDatabase::CreateSourceVoice()
{
	for (int loop = 0 ; loop < sedata::MAX_SE ; ++loop)
	{
		m_sourceWaveFormat[loop] = new CLoadWave(sedata::SEName[loop]);
		m_SeVoices[loop] = NULL;
	}

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		WAVEFORMATEX* waveformat = m_sourceWaveFormat[loop]->GetWaveFormat();
		GetXAudio2Mgr()->SetXAudio2SouceVoice(&m_SeVoices[loop],*waveformat);
	}

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->SubmitSourceBuffer(&m_sourceWaveFormat[loop]->PreLoadSound());
	}

	Soundfunc = []() {};

}

///////////////////////////////////////////////////////////
//
//	���ӂ����Ƃ̂����Ă�
//
void CSEDatabase::CreateVoiceEffect()
{

	// �e��̐ݒ�
	CreateFX(__uuidof(::FXReverb), &m_Effect[0]);
	CreateFX(__uuidof(::FXEcho),&m_Effect[1]);
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

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->SetEffectChain(&m_chain);
	}

	// ���o�[�u�̏�����
	m_Reverbpram.Diffusion = FXREVERB_DEFAULT_DIFFUSION;
	m_Reverbpram.RoomSize = FXREVERB_DEFAULT_ROOMSIZE;

	// �G�R�[�̏�����
	m_EchoPram.Delay		= FXECHO_DEFAULT_DELAY;
	m_EchoPram.Feedback		= FXECHO_DEFAULT_FEEDBACK;
	m_EchoPram.WetDryMix	= FXECHO_DEFAULT_WETDRYMIX;

	FXECHO_MAX_DELAY;
	FXECHO_MAX_FEEDBACK;
	FXECHO_MAX_WETDRYMIX;

	// �C�R���C�U�̏�����
	m_EqPram.FrequencyCenter0 = FXEQ_DEFAULT_FREQUENCY_CENTER_0;
	m_EqPram.FrequencyCenter1 = FXEQ_DEFAULT_FREQUENCY_CENTER_1;
	m_EqPram.FrequencyCenter2 = FXEQ_DEFAULT_FREQUENCY_CENTER_2;
	m_EqPram.FrequencyCenter3 = FXEQ_DEFAULT_FREQUENCY_CENTER_3;

	// �F�X����Ă��邯�ǃ��o�[�u�̐ݒ肾�����Ă܂��B
	// ���ɂ��F�X����炵��
	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->SetEffectParameters(0, &m_Reverbpram, sizeof(FXREVERB_PARAMETERS));
		m_SeVoices[loop]->SetEffectParameters(1, &m_EchoPram, sizeof(FXECHO_PARAMETERS));
		m_SeVoices[loop]->SetEffectParameters(2, &m_EqPram, sizeof(FXEQ_PARAMETERS));
	}
}

///////////////////////////////////////////////////////////
//
//	�Đ�
//
void CSEDatabase::Play(int SeListNumb)
{
	m_SeVoices[SeListNumb]->Start();
}

///////////////////////////////////////////////////////////
//
//	��~
//
void CSEDatabase::Stop(int SeListNumb)
{
	m_SeVoices[SeListNumb]->Stop();
}

///////////////////////////////////////////////////////////
//
//	�X�V����
//
void CSEDatabase::Update()
{
	if (Soundfunc != NULL)
	{
		Soundfunc();
	}
}

///////////////////////////////////////////////////////////
//
//	��������
//
void CSEDatabase::Close()
{
	// ���Ǝn��
	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->DestroyVoice();
	}

	// 
	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		delete m_sourceWaveFormat[loop];
	}

	//m_Effects->Release();
}

///////////////////////////////////////////////////////////
//
//	���݃{�����[���̎擾
//
float CSEDatabase::GetSeVolume()
{
	return Volume;
}

///////////////////////////////////////////////////////////
//
//	Se�̑S�̉��ʂ̐ݒ�
//
void CSEDatabase::SetSeVolume(float Vol)
{
	Volume = Vol;

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->SetVolume(Volume);
	}
}

///////////////////////////////////////////////////////////
//
//	�s�b�`���[�g�̕ύX
//
void CSEDatabase::PitchRate(int BgmListNumb, float PitchRate)
{
	m_SeVoices[BgmListNumb]->SetFrequencyRatio(PitchRate);
}

///////////////////////////////////////////////////////////
//
//	Reverb�G�t�F�N�g�̐ݒ�
//
void CSEDatabase::SetReverbSize(float walltype, float roomsize)
{
	FXREVERB_PARAMETERS param;

	param.Diffusion = walltype;
	param.RoomSize = roomsize;

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->SetEffectParameters(0, &param, sizeof(FXREVERB_PARAMETERS));
	}
}

///////////////////////////////////////////////////////////
//
//	Reverb������
//
void CSEDatabase::offsetReverbSize()
{
	FXREVERB_PARAMETERS param;

	param.Diffusion = FXREVERB_DEFAULT_DIFFUSION;
	param.RoomSize  = FXREVERB_DEFAULT_ROOMSIZE;

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->SetEffectParameters(0, &param, sizeof(FXREVERB_PARAMETERS));
	}
}
///////////////////////////////////////////////////////////
//
//	Reverb������
//
void CSEDatabase::SetEchoSize(float Delay,float feedback,float wetdry)
{
	FXECHO_PARAMETERS param;

	param.Delay = Delay;
	param.Feedback = feedback;
	param.WetDryMix = wetdry;

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->SetEffectParameters(1, &param, sizeof(FXECHO_PARAMETERS));
	}
}