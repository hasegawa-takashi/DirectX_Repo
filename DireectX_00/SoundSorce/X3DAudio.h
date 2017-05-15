#pragma once

#include<vector>
#include<X3DAudio.h>



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

	void SetListener(D3DMATRIX* matrix);

private:
	X3DAUDIO_LISTENER m_listener;
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
