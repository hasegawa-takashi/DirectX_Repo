#pragma once


#include<d3d9.h>
#include<X3DAudio.h>
#include<vector>
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

	void SetEmitter(D3DMATRIX* matrix);
	void Update();

private:
	std::vector<D3DMATRIX*> m_Emitterlist;
	//std::list<X3DAUDIO_EMITTER> m_emitter;
	X3DAUDIO_EMITTER m_Emitter;

};
