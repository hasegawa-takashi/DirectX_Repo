#pragma once

#include<d3dx9.h>

class  CCalculation
{
private:
	CCalculation();
	~CCalculation();

public:

	///////////////////////////////////
	// --- �ǂ���x�N�g��
	static D3DXVECTOR3* calcWallScratchVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal);

	//////////////////////////////////
	// --- ���˃x�N�g��
	static D3DXVECTOR3* calcReflectVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal);

	//---------------------------------------
	// �N�I�[�^�j�I�����s��v�Z
	static void QuaternionToMatrix(D3DXMATRIX &mat, D3DXQUATERNION Qua);

	//---------------------------------------
	// �s��v�Z���N�I�[�^�j�I��
	static bool MatrixToQuaternion(D3DXMATRIX mat, D3DXQUATERNION &Qua);

	//---------------------------------------
	// �p���s��̐ݒ�
	static D3DXMATRIX* CalcLookAtMatrix(D3DXMATRIX* mat, D3DXVECTOR3* pPos, D3DXVECTOR3* pLook, D3DXVECTOR3* pUp);

	//---------------------------------------
	// �p���s��(Y���̂�)�̐ݒ�
	static D3DXMATRIX* CalcLookAtMatrixFix(D3DXMATRIX* mat, D3DXVECTOR3* pPos, D3DXVECTOR3* pLook, D3DXVECTOR3* pUp);

	//---------------------------------------
	// ��̃x�N�g���̊p�x�����߂�
	static double AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B);
	
};

