#pragma once

class CSoundComponent;
#include"../../Sound.h"
#include"../SoundComponent/SoundComponent.h"
#include"../../../Calculation.h"
#include"../../XAudio2/X3DAudio/X3DSound/X3DSound.h"

/*
*
* CListenerComponent
*	���X�i�[��ݒ肷��p��Component
*
*/
class CListenerComponent 
	: public CSoundComponent
{
public:
	CListenerComponent();
	~CListenerComponent();

	void Init(D3DXMATRIX* matrix);

	// �X�V����
	void ComponentUpdate() override;

	void SetListener(D3DXMATRIX* matrix);

private:
	X3DAUDIO_LISTENER m_listener;
	D3DXMATRIX* m_listenerMtx;
	bool m_Uselistener;
};