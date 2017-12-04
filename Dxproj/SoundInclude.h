#pragma once
/// <summary>
/// サウンドを扱うときに使用するヘッダーファイル
/// </summary>
#include"Sound\AudioDatabase\AudioDatabase.h"
#include"Component.h"
#include"Sound\AudioComponent\SoundPlayerComponent\SoundPlayerComponent.h"
#include"Sound\AudioComponent\SoundEffectComponent\SoundEffectComponent.h"
#include"Sound\AudioComponent\ListenerComponent\ListenerComponent.h"
#include"Sound\AudioComponent\EmitterComponent\EmitterComponent.h"


/**
これを操作する用のInterfaceを作ったほうが管理が簡単
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

