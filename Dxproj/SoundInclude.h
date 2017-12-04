#pragma once
/// <summary>
/// �T�E���h�������Ƃ��Ɏg�p����w�b�_�[�t�@�C��
/// </summary>
#include"Sound\AudioDatabase\AudioDatabase.h"
#include"Component.h"
#include"Sound\AudioComponent\SoundPlayerComponent\SoundPlayerComponent.h"
#include"Sound\AudioComponent\SoundEffectComponent\SoundEffectComponent.h"
#include"Sound\AudioComponent\ListenerComponent\ListenerComponent.h"
#include"Sound\AudioComponent\EmitterComponent\EmitterComponent.h"


/**
����𑀍삷��p��Interface��������ق����Ǘ����ȒP
*/
struct AudioComponent
{
	Component Comp;
	IXAudio2SourceVoice* Sourcevoice;
	CSoundPlayerComponent* Playercomp;
	CListenerComponent* ListenerComp;
	CEmitterComponent* EmitterComp;
	CSoundEffectComponent* EffectComp;
};

