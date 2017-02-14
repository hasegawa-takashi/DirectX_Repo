#pragma once

#include<d3d9.h>
#include<math.h>
#include"Window.h"

class CCalculation
{
public:
	CCalculation();
	~CCalculation();

	///////////////////////////////////
	// --- �ǂ���x�N�g��
	D3DXVECTOR3* calcWallScratchVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal);

	//////////////////////////////////
	// --- ���˃x�N�g��
	D3DXVECTOR3* calcReflectVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal);

};

