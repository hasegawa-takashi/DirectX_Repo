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
//	二つのベクトルの角度を求める
//
double CCalculation::AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B)
{
	//　※ベクトルの長さが0だと答えが出ませんので注意してください。

	//ベクトルAとBの長さを計算する
	double length_A = D3DXVec3Length(&A);
	double length_B = D3DXVec3Length(&B);

	//内積とベクトル長さを使ってcosθを求める
	double cos_sita = D3DXVec3Dot(&A, &B) / (length_A * length_B);

	//cosθからθを求める
	double sita = acos(cos_sita);


	sita = sita * 180.0 / D3DX_PI;

	return sita;
}