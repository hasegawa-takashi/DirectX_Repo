#pragma once

#include<d3dx9.h>

class  CCalculation
{
private:
	CCalculation();
	~CCalculation();

public:

	///////////////////////////////////
	// --- 壁ずりベクトル
	static D3DXVECTOR3* calcWallScratchVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal);

	//////////////////////////////////
	// --- 反射ベクトル
	static D3DXVECTOR3* calcReflectVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal);

	//---------------------------------------
	// クオータニオン→行列計算
	static void QuaternionToMatrix(D3DXMATRIX &mat, D3DXQUATERNION Qua);

	//---------------------------------------
	// 行列計算→クオータニオン
	static bool MatrixToQuaternion(D3DXMATRIX mat, D3DXQUATERNION &Qua);

	//---------------------------------------
	// 姿勢行列の設定
	static D3DXMATRIX* CalcLookAtMatrix(D3DXMATRIX* mat, D3DXVECTOR3* pPos, D3DXVECTOR3* pLook, D3DXVECTOR3* pUp);

	//---------------------------------------
	// 姿勢行列(Y軸のみ)の設定
	static D3DXMATRIX* CalcLookAtMatrixFix(D3DXMATRIX* mat, D3DXVECTOR3* pPos, D3DXVECTOR3* pLook, D3DXVECTOR3* pUp);

	//---------------------------------------
	// 二つのベクトルの角度を求める
	static double AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B);
	
};

