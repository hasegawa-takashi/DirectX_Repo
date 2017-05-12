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
	CreateFX(__uuidof(::FXReverb), &m_Effects);

	m_desc.InitialState = TRUE;
	m_desc.OutputChannels = 2;
	m_desc.pEffect = m_Effects;

	m_chain.pEffectDescriptors = &m_desc;
	m_chain.EffectCount = 1;

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->SetEffectChain(&m_chain);
	}

	// ���o�[�u�̏�����
	m_Reverbpram.Diffusion = FXREVERB_DEFAULT_DIFFUSION;
	m_Reverbpram.RoomSize = FXREVERB_DEFAULT_ROOMSIZE;

	// �G�R�[�̏�����
	m_EchoPram.Delay = FXECHO_DEFAULT_DELAY;
	m_EchoPram.Feedback = FXECHO_DEFAULT_FEEDBACK;
	m_EchoPram.WetDryMix = FXECHO_DEFAULT_WETDRYMIX;

	// �C�R���C�U�̏�����
	m_EqPram.FrequencyCenter0 = FXEQ_DEFAULT_FREQUENCY_CENTER_0;
	m_EqPram.FrequencyCenter1 = FXEQ_DEFAULT_FREQUENCY_CENTER_1;
	m_EqPram.FrequencyCenter2 = FXEQ_DEFAULT_FREQUENCY_CENTER_2;
	m_EqPram.FrequencyCenter3 = FXEQ_DEFAULT_FREQUENCY_CENTER_3;

	// �F�X����Ă��邯�ǃ��o�[�u�̐ݒ肾�����Ă܂��B
	// ���ɂ��F�X����炵��
	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		//m_SeVoices[loop]->SetEffectParameters(0, &m_Reverbpram, sizeof(FXREVERB_PARAMETERS));
		//m_SeVoices[loop]->SetEffectParameters(1, &m_EchoPram, sizeof(FXREVERB_PARAMETERS));
		//m_SeVoices[loop]->SetEffectParameters(2, &m_EqPram, sizeof(FXREVERB_PARAMETERS));
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

	m_Effects->Release();
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
	param.RoomSize = FXREVERB_DEFAULT_ROOMSIZE;

	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->SetEffectParameters(0, &param, sizeof(FXREVERB_PARAMETERS));
	}
}