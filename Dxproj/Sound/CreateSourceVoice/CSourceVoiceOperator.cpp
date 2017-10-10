#include "CSourceVoiceOperator.h"

//============================================
//
//	�K�v�ϐ��̏�����
//
CSourceVoiceOperator::CSourceVoiceOperator()
{
	m_Identity = 0;
	m_MasterVolume = 0;
}

//============================================
//
//	�{�C�X�̑S�폜
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
//	Stream�Đ��o�^
//		element = �g�pwav�f�[�^
int CSourceVoiceOperator::RegistVoice(SoundElement element)
{
	// ������
	VoiceElement* voiceelemnt;
	voiceelemnt->Wavedata = element;
	voiceelemnt->Soundfunc = nullptr;
	voiceelemnt->IdentNumb = m_Identity++;

	// �V�KSource�{�C�X(VoiceElement)��o�^
	GetXAudio2Mgr()->SetXAudio2SourceVoice(&voiceelemnt->Sourcevoice, *voiceelemnt->Wavedata.Waveformat );
	
	// buffer�̐ݒ�
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
	
	// Effect�̐ݒ�
	voiceelemnt->Effect = new CVoiceEffect(voiceelemnt->Sourcevoice);
	
	// �o�^�I��
	m_Voicelist.push_back(voiceelemnt);

	// �ŗL�ԍ���Ԃ�
	return voiceelemnt->IdentNumb;
}

#pragma region �Đ�
//==========================================================
//
//	�Đ�
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
//	�Đ�(Fade On)
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

#pragma region ��~�n
//==========================================================
//
//	��~
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
//	��~ (Fade on)
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
//	�X�V
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

		// Preload����
		if (var->Wavedata.StreamType == 0)
			continue;
			
		XAUDIO2_BUFFER buffer = var->Wavedata.Loadsoundfile->UpdateBuffer(var->Sourcevoice);

		// ���[�v�Đ��p
		if (buffer.pAudioData > 0 && var->Wavedata.Loop)
			var->Sourcevoice->SubmitSourceBuffer(&buffer);
	}
}

#pragma region Fade�n
//==========================================================
//
//	FadeIn����
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
//	�T�E���h��Fadeout
//
void CSourceVoiceOperator::FadeOut(float fadespd, VoiceElement* sourcevoice)
{
	// Sound�̎擾
	float NowVolume = 0.0f;
	sourcevoice->Sourcevoice->GetVolume(&NowVolume);
	// Fade�I��
	if (NowVolume <= 0)
	{
		sourcevoice->Sourcevoice->SetVolume(0.0f);
		sourcevoice->Sourcevoice->Stop();
		sourcevoice->Soundfunc = nullptr;
	}
	// Sound�̉��ʂ̐ݒ�
	NowVolume -= fadespd;
	sourcevoice->Sourcevoice->SetVolume(NowVolume);
}
#pragma endregion

#pragma region �G�t�F�N�g�̕ύX
//==========================================================
//
//	���o�[�u
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
//	�G�R�[
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
//	�s�b�`
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

#pragma region �G�t�F�N�g��OFF
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
