
#include<X3DAudio.h>
#include<list>

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

	void SetListener();

	

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

	void SetEmitter();

private:
	std::list<X3DAUDIO_EMITTER> m_emitter;

};
