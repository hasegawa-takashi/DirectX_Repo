#pragma once


#include<d3d9.h>
#include<X3DAudio.h>
#include"XAudio2Interface.h"
#include"../Calculation.h"

#pragma comment(lib,"X3daudio.lib")

//------------------------------------------------------------
//
//	���̒��S�n
//	�L�����N�^�[��J�����ɂ��̂ň�ő����
//
//------------------------------------------------------------
class CListener
{
public:
	CListener();
	~CListener();

	void Update();

	void SetListener(D3DXMATRIX* matrix);

private:
	X3DAUDIO_LISTENER m_listener;
	D3DXMATRIX* m_listenerMtx;

	bool m_Uselistener;

};


//------------------------------------------------------------
//
//	���̔��M�n
//	�����o�����̂̐������K�v�Ȃ̂�list�Ǘ�
//
//------------------------------------------------------------
class CEmitter
{
public:
	CEmitter();
	~CEmitter();

	void SetEmitter(D3DXMATRIX* matrix);
	void Update();

private:
	D3DXMATRIX* m_EmitterMatrix;
	X3DAUDIO_EMITTER m_Emitter;

};

//------------------------------------------------------------
//
//	3DAudio���܂Ƃ߂Ă���
//
//------------------------------------------------------------
class C3DSound
{
public:
	C3DSound();
	~C3DSound();

	bool SetListener(D3DXMATRIX** matrix);

	X3DAUDIO_DSP_SETTINGS Calc3DAudio(D3DXMATRIX* emitter);

private:
	X3DAUDIO_HANDLE			m_X3DInstance;			//
	X3DAUDIO_DSP_SETTINGS	m_X3DDsp;				// 
	CListener*				m_VoiceListener;		// (���S�n :: �o�^��)
	CEmitter*				m_Emitter;				// (���M�n :: ������)

};

