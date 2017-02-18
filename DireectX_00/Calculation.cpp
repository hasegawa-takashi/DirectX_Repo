#include "Calculation.h"



CCalculation::CCalculation()
{
}


CCalculation::~CCalculation()
{
}

//////////////////////////////////
// 壁ずりベクトル
//
// out : 正規化壁ずりベクトル（戻り値）
// front : 進行ベクトル
// normal: 衝突点での法線ベクトル
//
D3DXVECTOR3* CCalculation::calcWallScratchVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal) {
	D3DXVECTOR3 normal_n;
	D3DXVec3Normalize(&normal_n, &normal);
	return D3DXVec3Normalize(out, &(front - D3DXVec3Dot(&front, &normal_n) * normal_n));
}

//////////////////////////////////
// 反射ベクトル
//
// out : 正規化反射ベクトル（戻り値）
// front : 進行ベクトル
// normal: 衝突点での法線ベクトル
//
D3DXVECTOR3* CCalculation::calcReflectVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal) {
	D3DXVECTOR3 normal_n;
	D3DXVec3Normalize(&normal_n, &normal);
	return D3DXVec3Normalize(out, &(front - 2.0f * D3DXVec3Dot(&front, &normal_n) * normal_n));
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	クオータニオン行列→回転行列への変換
//
void CCalculation::QuaternionToMatrix(D3DXMATRIX &mat,D3DXQUATERNION Qua)
{
	mat._11 = 1.0f - 2.0f * Qua.y * Qua.y - 2.0f * Qua.z * Qua.z;
	mat._12 = 2.0f * Qua.x * Qua.y + 2.0f * Qua.w * Qua.z;
	mat._13 = 2.0f * Qua.x * Qua.z - 2.0f * Qua.w * Qua.y;
	mat._21 = 2.0f * Qua.x * Qua.y - 2.0f * Qua.w * Qua.z;
	mat._22 = 1.0f - 2.0f * Qua.x * Qua.x - 2.0f * Qua.z * Qua.z;
	mat._23 = 2.0f * Qua.y * Qua.z + 2.0f * Qua.w * Qua.x;
	mat._31 = 2.0f * Qua.x * Qua.z + 2.0f * Qua.w * Qua.y;
	mat._32 = 2.0f * Qua.y * Qua.z - 2.0f * Qua.w * Qua.x;
	mat._33 = 1.0f - 2.0f * Qua.x * Qua.x - 2.0f * Qua.y * Qua.y;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	回転行列→クオータニオン
//
bool CCalculation::MatrixToQuaternion(D3DXMATRIX mat, D3DXQUATERNION &Qua)
{
	// 最大成分を検索
	float elem[4]; // 0:x, 1:y, 2:z, 3:w
	elem[0] = mat._11 - mat._22 - mat._33 + 1.0f;
	elem[1] = -mat._11 + mat._22 - mat._33 + 1.0f;
	elem[2] = -mat._11 - mat._22 + mat._33 + 1.0f;
	elem[3] = mat._11 + mat._22 + mat._33 + 1.0f;

	unsigned biggestIndex = 0;
	for (int i = 1; i < 4; i++) {
		if (elem[i] > elem[biggestIndex])
			biggestIndex = i;
	}

	if (elem[biggestIndex] < 0.0f)
		return false; // 引数の行列に間違いあり！

					  // 最大要素の値を算出
	float *q[4] = { &Qua.x, &Qua.y, &Qua.z, &Qua.w };
	float v = sqrtf(elem[biggestIndex]) * 0.5f;
	*q[biggestIndex] = v;
	float mult = 0.25f / v;

	switch (biggestIndex) {
	case 0: // x
		*q[1] = (mat._12 + mat._21) * mult;
		*q[2] = (mat._31 + mat._13) * mult;
		*q[3] = (mat._23 - mat._32) * mult;
		break;
	case 1: // y
		*q[0] = (mat._12 + mat._21) * mult;
		*q[2] = (mat._23 + mat._32) * mult;
		*q[3] = (mat._31 - mat._13) * mult;
		break;
	case 2: // z
		*q[0] = (mat._31 + mat._13) * mult;
		*q[1] = (mat._23 + mat._32) * mult;
		*q[3] = (mat._12 - mat._21) * mult;
		break;
	case 3: // w
		*q[0] = (mat._23 - mat._32) * mult;
		*q[1] = (mat._31 - mat._13) * mult;
		*q[2] = (mat._12 - mat._21) * mult;
		break;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	姿勢行列の計算(制限無し)
//
D3DXMATRIX* CCalculation::CalcLookAtMatrix(D3DXMATRIX* mat,D3DXVECTOR3* pPos, D3DXVECTOR3* pLook,D3DXVECTOR3* pUp)
{
	D3DXVECTOR3 X, Y, Z;
	Z = *pLook - *pPos;
	D3DXVec3Normalize(&Z, &Z);
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, pUp), &Z);
	D3DXVec3Normalize(&X, &X);
	D3DXVec3Normalize(&Y, D3DXVec3Cross(&Y, &Z, &X));


	mat->_11 = X.x; mat->_12 = X.y; mat->_13 = X.z; mat->_14 = 0;
	mat->_21 = Y.x; mat->_22 = Y.y; mat->_23 = Y.z; mat->_24 = 0;
	mat->_31 = Z.x; mat->_32 = Z.y; mat->_33 = Z.z; mat->_34 = 0;
	mat->_41 = 0.0f; mat->_42 = 0.0f; mat->_43 = 0.0f; mat->_44 = 1.0f;

	return mat;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	姿勢行列の計算(Y軸のみ)
//
D3DXMATRIX* CCalculation::CalcLookAtMatrixFix(D3DXMATRIX* mat, D3DXVECTOR3* pPos, D3DXVECTOR3* pLook, D3DXVECTOR3* pUp)
{
	D3DXVECTOR3 X, Y, Z, D;
	D = *pLook - *pPos;
	D3DXVec3Normalize(&D,&D);
	D3DXVec3Cross(&X,D3DXVec3Normalize(&Y,pUp),&D);
	D3DXVec3Normalize(&X,&X);
	D3DXVec3Normalize(&Z, D3DXVec3Cross(&Z,&X,&Y));

	mat->_11 = X.x; mat->_12 = X.y; mat->_13 = X.z; mat->_14 = 0;
	mat->_21 = Y.x; mat->_22 = Y.y; mat->_23 = Y.z; mat->_24 = 0;
	mat->_31 = Z.x; mat->_32 = Z.y; mat->_33 = Z.z; mat->_34 = 0;
	mat->_41 = 0.0f; mat->_42 = 0.0f; mat->_43 = 0.0f; mat->_44 = 1.0f;

	return mat;

}