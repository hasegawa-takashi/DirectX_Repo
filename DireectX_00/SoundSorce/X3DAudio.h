#pragma once


#include<d3d9.h>
#include<X3DAudio.h>
#include"XAudio2Interface.h"
#include"../Calculation.h"

#pragma comment(lib,"X3daudio.lib")

//------------------------------------------------------------
//
//	音の中心地
//	キャラクターやカメラにつくので一つで足りる
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
//	音の発信地
//	音を出すものの数だけ必要なのでlist管理
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
//	3DAudioをまとめてるやつ
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
	CListener*				m_VoiceListener;		// (中心地 :: 登録制)
	CEmitter*				m_Emitter;				// (発信地 :: 引数制)

};

