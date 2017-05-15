#pragma once

#include<list>
#include<X3DAudio.h>



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

	void SetListener(D3DMATRIX* matrix);

private:
	X3DAUDIO_LISTENER m_listener;
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

	void SetEmitter(D3DMATRIX* matrix);

private:
	std::list<X3DAUDIO_EMITTER> m_emitter;

};
