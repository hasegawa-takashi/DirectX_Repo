#pragma once

class CSoundComponent;
#include"../SoundComponent/SoundComponent.h"

#include"../../../Calculation.h"
#include"../../XAudio2/X3DAudio/X3DSound/X3DSound.h"
#include"../../XAudio2/XAudio2Interface/XAudioInterface.h"
/*
*
* CEmitterComponent
*	エミッターを設定する用のComponent
*
*/
class CEmitterComponent : public CSoundComponent
{
public:
	// 初期化込々
	CEmitterComponent();
	~CEmitterComponent();

	// しょきか
	void Init(IXAudio2SourceVoice** voice, D3DXMATRIX* matrix);

	// 更新処理
	void ComponentUpdate() override;

private:
	D3DXMATRIX*					m_EmitterMatrix;
	X3DAUDIO_EMITTER			m_Emitter;
	X3DAUDIO_DSP_SETTINGS		m_X3DDsp;

	IXAudio2SourceVoice* m_Voice;
	FLOAT32 emitterAzimuths[1];

	// XAudio2Sound3Dのsampleから抜き出し
	const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_LFE_CurvePoints[3] = { 0.0f, 1.0f, 0.25f, 0.0f, 1.0f, 0.0f };
	const X3DAUDIO_DISTANCE_CURVE       Emitter_LFE_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)&Emitter_LFE_CurvePoints[0], 3 };

	const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_Reverb_CurvePoints[3] = { 0.0f, 0.5f, 0.75f, 1.0f, 1.0f, 0.0f };
	const X3DAUDIO_DISTANCE_CURVE       Emitter_Reverb_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)&Emitter_Reverb_CurvePoints[0], 3 };
	const X3DAUDIO_CONE Listener_DirectionalCone = { X3DAUDIO_PI*5.0f / 6.0f, X3DAUDIO_PI*11.0f / 6.0f, 1.0f, 0.75f, 0.0f, 0.25f, 0.708f, 1.0f };

};

