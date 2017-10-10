#pragma once

class CSoundComponent;
#include"../../Sound.h"
#include"../SoundComponent/SoundComponent.h"
#include"../../../Calculation.h"
#include"../../XAudio2/X3DAudio/X3DSound/X3DSound.h"

/*
*
* CListenerComponent
*	リスナーを設定する用のComponent
*
*/
class CListenerComponent 
	: public CSoundComponent
{
public:
	CListenerComponent();
	~CListenerComponent();

	void Init(D3DXMATRIX* matrix);

	// 更新処理
	void ComponentUpdate() override;

	void SetListener(D3DXMATRIX* matrix);

private:
	X3DAUDIO_LISTENER m_listener;
	D3DXMATRIX* m_listenerMtx;
	bool m_Uselistener;
};