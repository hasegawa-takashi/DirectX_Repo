#pragma once
class ObjBase;
#include"includeheader.h"

/// <summary>
///	
/// </summary>
class CCamera : public CSingleton<CCamera>
{
public:
	CCamera();
	~CCamera();

	void Init();
	void LateUpdate();
	void LateDraw();
	void Release();
	void SetTargetObj(ObjBase* _target);

	void TargetMove() { m_MoveFlag = true; }
	D3DXVECTOR3 GetPosition() { return m_WorldPosition; }

private:
	
	void CameraInput();
	void TpsCamera();

	// カメラの設定変数
	D3DXVECTOR3 m_LocalPosition;	// 回転差異分の座標
	D3DXVECTOR3 m_WorldPosition;	// TargetPosition適応後の座標
	D3DXVECTOR3 m_LookPosDeviation;	// 注視点の移動差分
	D3DXVECTOR3 m_DirDef;			// カメラの向き
	D3DXVECTOR3 m_Upvec;			// 上
	D3DXVECTOR3 m_LookAtPos;
	D3DXVECTOR3 m_CameraMove;		// 速度


	D3DXMATRIX m_WorldMatrix;			// Objのワールド行列
	D3DXMATRIX m_ViewMatrix;
	D3DXMATRIX m_PoseMatrix;
	D3DXMATRIX m_ProjectionMatrix;

	float m_Distance;
	float m_Zrot;
	float m_AngleUnit;			// 移動時の回転単位 = カメラの移動速度
	float m_OffsetZ;

	bool m_MoveFlag;			// 対象の移動検知

	ObjBase* m_TargetObj;

};

