#include "SEDatabase.h"

///////////////////////////////////////////////////////////
//
//	準備
//
CSEDatabase::CSEDatabase()
{
	CreateSourceVoice();
	CreateVoiceEffect();

	Volume = 1.0f;

}

///////////////////////////////////////////////////////////
//
//	かたずけ
//
CSEDatabase::~CSEDatabase()
{
	Close();
}

///////////////////////////////////////////////////////////
//
//	ソースボイスのせってい
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
//	えふぇくとのせってい
//
void CSEDatabase::CreateVoiceEffect()
{

	// 各種の設定
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

	// リバーブの初期化
	m_Reverbpram.Diffusion = FXREVERB_DEFAULT_DIFFUSION;
	m_Reverbpram.RoomSize = FXREVERB_DEFAULT_ROOMSIZE;

	// エコーの初期化
	m_EchoPram.Delay		= FXECHO_DEFAULT_DELAY;
	m_EchoPram.Feedback		= FXECHO_DEFAULT_FEEDBACK;
	m_EchoPram.WetDryMix	= FXECHO_DEFAULT_WETDRYMIX;

	FXECHO_MAX_DELAY;
	FXECHO_MAX_FEEDBACK;
	FXECHO_MAX_WETDRYMIX;

	// イコライザの初期化
	m_EqPram.FrequencyCenter0 = FXEQ_DEFAULT_FREQUENCY_CENTER_0;
	m_EqPram.FrequencyCenter1 = FXEQ_DEFAULT_FREQUENCY_CENTER_1;
	m_EqPram.FrequencyCenter2 = FXEQ_DEFAULT_FREQUENCY_CENTER_2;
	m_EqPram.FrequencyCenter3 = FXEQ_DEFAULT_FREQUENCY_CENTER_3;

	// 色々やっているけどリバーブの設定だけしてます。
	// 他にも色々あるらしい
	for (int loop = 0; loop < sedata::MAX_SE; ++loop)
	{
		m_SeVoices[loop]->SetEffectParameters(0, &m_Reverbpram, sizeof(FXREVERB_PARAMETERS));
		m_SeVoices[loop]->SetEffectParameters(1, &m_EchoPram, sizeof(FXECHO_PARAMETERS));
		m_SeVoices[loop]->SetEffectParameters(2, &m_EqPram, sizeof(FXEQ_PARAMETERS));
	}
}

///////////////////////////////////////////////////////////
//
//	再生
//
void CSEDatabase::Play(int SeListNumb)
{
	m_SeVoices[SeListNumb]->Start();
}

///////////////////////////////////////////////////////////
//
//	停止
//
void CSEDatabase::Stop(int SeListNumb)
{
	m_SeVoices[SeListNumb]->Stop();
}

///////////////////////////////////////////////////////////
//
//	更新処理
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
//	かたずけ
//
void CSEDatabase::Close()
{
	// あと始末
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
//	現在ボリュームの取得
//
float CSEDatabase::GetSeVolume()
{
	return Volume;
}

///////////////////////////////////////////////////////////
//
//	Seの全体音量の設定
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
//	ピッチレートの変更
//
void CSEDatabase::PitchRate(int BgmListNumb, float PitchRate)
{
	m_SeVoices[BgmListNumb]->SetFrequencyRatio(PitchRate);
}

///////////////////////////////////////////////////////////
//
//	Reverbエフェクトの設定
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
//	Reverb初期化
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
//	Reverb初期化
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