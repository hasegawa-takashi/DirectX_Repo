#include "CSourceVoiceOperator.h"

//============================================
//
//	必要変数の初期化
//
CSourceVoiceOperator::CSourceVoiceOperator()
{
	m_Identity = 0;
	m_MasterVolume = 0;
}

//============================================
//
//	ボイスの全削除
//
CSourceVoiceOperator::~CSourceVoiceOperator()
{
	for each (auto var in m_Voicelist)
	{
		var->Sourcevoice->DestroyVoice();
		delete var->Wavedata.Loadsoundfile;
		delete var->Wavedata.Waveformat;
		delete var->Effect;
		var->Soundfunc = nullptr;
	}
}

//==========================================================
//
//	Stream再生登録
//		element = 使用wavデータ
int CSourceVoiceOperator::RegistVoice(SoundElement element)
{
	// 初期化
	VoiceElement* voiceelemnt;
	voiceelemnt->Wavedata = element;
	voiceelemnt->Soundfunc = nullptr;
	voiceelemnt->IdentNumb = m_Identity++;

	// 新規Sourceボイス(VoiceElement)を登録
	GetXAudio2Mgr()->SetXAudio2SourceVoice(&voiceelemnt->Sourcevoice, *voiceelemnt->Wavedata.Waveformat );
	
	// bufferの設定
	switch (element.StreamType)
	{
	case 0:
		voiceelemnt->Sourcevoice->SubmitSourceBuffer(&voiceelemnt->Wavedata.Loadsoundfile->PreloadBuffer());
		break;
	case 1:
		voiceelemnt->Sourcevoice->SubmitSourceBuffer(&voiceelemnt->Wavedata.Loadsoundfile->StreamloadBuffer());
		break;
	default:
		printf("StreamTypeErro");
		break;
	}
	
	// Effectの設定
	voiceelemnt->Effect = new CVoiceEffect(voiceelemnt->Sourcevoice);
	
	// 登録終了
	m_Voicelist.push_back(voiceelemnt);

	// 固有番号を返す
	return voiceelemnt->IdentNumb;
}

#pragma region 再生
//==========================================================
//
//	再生
//
void CSourceVoiceOperator::VoicePlay(int identnumb)
{
	for each (auto var in m_Voicelist)
	{
		if (var->IdentNumb != identnumb)
			continue;

		var->Sourcevoice->Start();
		break;
	}
}

//==========================================================
//
//	再生(Fade On)
//
void CSourceVoiceOperator::VoicePlay(int identnumb, float fadespd)
{
	for each (auto var in m_Voicelist)
	{
		if (var->IdentNumb != identnumb)
			continue;

		var->Soundfunc = std::bind(&CSourceVoiceOperator::FadeIn,this,fadespd,var);
		var->Sourcevoice->Start();
		break;
	}
}
#pragma endregion

#pragma region 停止系
//==========================================================
//
//	停止
//
void CSourceVoiceOperator::VoiceStop(int identnumb)
{
	for each (auto var in m_Voicelist)
	{
		if (var->IdentNumb != identnumb)
			continue;
		var->Sourcevoice->Stop();
		break;
	}
}

//==========================================================
//
//	停止 (Fade on)
//
void CSourceVoiceOperator::VoiceStop(int identnumb, float fadespd)
{
	for each (auto var in m_Voicelist)
	{
		if (var->IdentNumb != identnumb)
			continue;
		var->Soundfunc = std::bind(&CSourceVoiceOperator::FadeOut, this, fadespd, var);
		break;
	}
}
#pragma endregion

//==========================================================
//
//	更新
//
void CSourceVoiceOperator::Update()
{
	if (m_Voicelist.empty())
		return;

	for each (auto var in m_Voicelist)
	{
		
		if (var->Soundfunc != nullptr)
		{
			var->Soundfunc();
		}

		// Preload判定
		if (var->Wavedata.StreamType == 0)
			continue;
			
		XAUDIO2_BUFFER buffer = var->Wavedata.Loadsoundfile->UpdateBuffer(var->Sourcevoice);

		// ループ再生用
		if (buffer.pAudioData > 0 && var->Wavedata.Loop)
			var->Sourcevoice->SubmitSourceBuffer(&buffer);
	}
}

#pragma region Fade系
//==========================================================
//
//	FadeIn処理
//
void CSourceVoiceOperator::FadeIn(float fadespd, VoiceElement* sourcevoice)
{
	float NowVolume = 0.0f;
	sourcevoice->Sourcevoice->GetVolume(&NowVolume);

	if (sourcevoice->Wavedata.MaxVolume >= NowVolume)
	{
		sourcevoice->Sourcevoice->SetVolume(NowVolume);
		sourcevoice->Soundfunc = nullptr;
	}

	NowVolume += fadespd;
	sourcevoice->Sourcevoice->SetVolume(NowVolume);
}

//======================================================
//
//	サウンドのFadeout
//
void CSourceVoiceOperator::FadeOut(float fadespd, VoiceElement* sourcevoice)
{
	// Soundの取得
	float NowVolume = 0.0f;
	sourcevoice->Sourcevoice->GetVolume(&NowVolume);
	// Fade終了
	if (NowVolume <= 0)
	{
		sourcevoice->Sourcevoice->SetVolume(0.0f);
		sourcevoice->Sourcevoice->Stop();
		sourcevoice->Soundfunc = nullptr;
	}
	// Soundの音量の設定
	NowVolume -= fadespd;
	sourcevoice->Sourcevoice->SetVolume(NowVolume);
}
#pragma endregion

#pragma region エフェクトの変更
//==========================================================
//
//	リバーブ
//
void CSourceVoiceOperator::ChangeReverb(int identnumb, float walltype, float roomsize)
{
	for each (auto var in m_Voicelist)
	{
		if (var->IdentNumb != identnumb)
			continue;

		var->Effect->SetReverbVolume(walltype, roomsize);
		break;
	}
}

//==========================================================
//
//	エコー
//
void CSourceVoiceOperator::ChangeEcho(int identnumb, float Delay, float feedback, float wetdry)
{
	for each (auto var in m_Voicelist)
	{
		if (var->IdentNumb != identnumb)
			continue;

		var->Effect->SetEchoVolume(Delay, feedback, wetdry);
		break;
	}
}

//==========================================================
//
//	ピッチ
//
void CSourceVoiceOperator::ChangePitch(int identnumb, float PitchRate)
{
	for each (auto var in m_Voicelist)
	{
		if (var->IdentNumb != identnumb)
			continue;

		var->Effect->SetPitchRate(PitchRate);
		break;
	}
}
#pragma endregion

#pragma region エフェクトのOFF
void CSourceVoiceOperator::OffReverb(int identnumb)
{
	for each (auto var in m_Voicelist)
	{
		if (var->IdentNumb != identnumb)
			continue;
		var->Effect->offsetReverbVolume();
		break;
	}
}

void CSourceVoiceOperator::OffEcho(int identnumb)
{
	for each (auto var in m_Voicelist)
	{
		if (var->IdentNumb != identnumb)
			continue;
		var->Effect->offsetEchoVolume();
		break;
	}
}

void CSourceVoiceOperator::OffPitch(int identnumb)
{
	for each (auto var in m_Voicelist)
	{
		if (var->IdentNumb != identnumb)
			continue;
		var->Effect->offsetPitchRate();
		break;
	}
}
#pragma endregion
