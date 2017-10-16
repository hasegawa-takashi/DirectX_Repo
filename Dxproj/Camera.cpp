#include "Camera.h"



CCamera::CCamera()
{
	D3DXMatrixIdentity(&m_ViewMatrix);
	D3DXMatrixIdentity(&m_ProjectionMatrix);
	D3DXMatrixIdentity(&m_PoseMatrix);
	
	m_Zrot = 0.0f;
	m_OffsetZ = 10.0f;
	m_Distance = 5.0f;
	m_AngleUnit = 0.1f;

	m_LookAtPos = D3DXVECTOR3(0,0,0);
	m_WorldPosition = D3DXVECTOR3(0, 0, 0);
	m_LocalPosition = D3DXVECTOR3(0, m_Distance, -1);
	m_DirDef = D3DXVECTOR3(0, 0, 0);
	m_Upvec = D3DXVECTOR3(0, 1, 0);
	

	memcpy(m_PoseMatrix.m[0], &D3DXVECTOR3(1, 0, 0), sizeof(D3DXVECTOR3));
	memcpy(m_PoseMatrix.m[1], &D3DXVECTOR3(0, 1, 0), sizeof(D3DXVECTOR3));
	memcpy(m_PoseMatrix.m[2], &D3DXVECTOR3(0, 0, 1), sizeof(D3DXVECTOR3));


	m_MoveFlag = true;
}


CCamera::~CCamera()
{
}

void CCamera::Init()
{

}

void CCamera::LateUpdate()
{
	CameraInput();
	
	TpsCamera();
	
	// 追従移動
	D3DXVECTOR3 _move = m_TargetObj->GetPosition();
	m_LookAtPos = _move;
	if (m_MoveFlag)
	{
		// Targetの座標
		m_WorldPosition = _move;

		// 現在の球面上の座標の追加
		
		m_MoveFlag = false;
	}

	D3DXVECTOR3 _ConvertPos;
	_ConvertPos = m_WorldPosition + m_LocalPosition;

	// ビュー行列の更新
	D3DXMatrixLookAtLH(&m_ViewMatrix,&_ConvertPos, &m_LookAtPos,&m_Upvec);

	// 
	memset(&m_DirDef, 0, sizeof(D3DXVECTOR3));
	memset(&m_CameraMove, 0, sizeof(D3DXVECTOR3));


}

void CCamera::LateDraw()
{


	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, FOVY, CWindowCreate::Getintance().GetASPECT(), NEAR_CLIP, FAR_CLIP);

	CDirectxMgr::Getintance().GetDxDevice()->SetTransform(D3DTS_PROJECTION, &m_ProjectionMatrix);
	CDirectxMgr::Getintance().GetDxDevice()->SetTransform(D3DTS_VIEW, &m_ViewMatrix);


	CDebug::Getintance().Conversion("\nカメラ座標", m_WorldPosition);

}

void CCamera::Release()
{

}

void CCamera::SetTargetObj(ObjBase* _target)
{
	m_TargetObj = _target;
}

void CCamera::TpsCamera()
{
	D3DXMATRIX mtxZrot;
	D3DXMatrixRotationZ(&mtxZrot, m_Zrot);
	m_PoseMatrix = mtxZrot *m_PoseMatrix;

	m_PoseMatrix._21 = 0.0f;
	m_PoseMatrix._22 = 1.0f;
	m_PoseMatrix._23 = 0.0f;

	D3DXVECTOR3 DL;
	D3DXVec3TransformCoord(&DL, &m_DirDef, &m_PoseMatrix);

	D3DXVECTOR3 RotAxis;

	D3DXVECTOR3* camZAxis = (D3DXVECTOR3*)m_PoseMatrix.m[2];
	D3DXVec3Cross(&RotAxis, &DL, camZAxis);

	D3DXQUATERNION TransQ;
	D3DXQuaternionRotationAxis(&TransQ, &RotAxis, m_AngleUnit);

	D3DXMATRIX TransRotMat;
	D3DXMatrixRotationQuaternion(&TransRotMat, &TransQ);
	D3DXVec3TransformCoord(&m_LocalPosition, &m_LocalPosition, &TransRotMat);

	// 移動後のカメラ姿勢の更新
	D3DXVECTOR3 X, Y, Z;

	Z = -m_LocalPosition;
	D3DXVec3Normalize(&Z, &Z);

	memcpy(&Y, m_PoseMatrix.m[1], sizeof(D3DXVECTOR3));
	D3DXVec3Cross(&X, &Y, &Z);
	D3DXVec3Normalize(&X, &X);

	D3DXVec3Cross(&Y, &Z, &X);
	D3DXVec3Normalize(&Y, &Y);

	D3DXMatrixIdentity(&m_PoseMatrix);
	memcpy(m_PoseMatrix.m[0], &X, sizeof(D3DXVECTOR3));
	memcpy(m_PoseMatrix.m[1], &Y, sizeof(D3DXVECTOR3));
	memcpy(m_PoseMatrix.m[2], &Z, sizeof(D3DXVECTOR3));

	// 奥行きの設定
	m_Distance = D3DXVec3Length(&m_LocalPosition);
	if (m_Distance - m_OffsetZ > 0) {
		D3DXVECTOR3 Z = -m_LocalPosition;
		D3DXVec3Normalize(&Z, &Z);
		m_LocalPosition += m_OffsetZ * Z;
		m_Distance -= m_OffsetZ;
	}

}

void CCamera::CameraInput()
{
	if (CInput::GetMouseAxis(MOUSE_X)) {
		m_CameraMove.x -= (CInput::GetMouseAxis(MOUSE_X));
	}

	if (CInput::GetMouseAxis(MOUSE_Y)) {
		m_CameraMove.y -= (CInput::GetMouseAxis(MOUSE_Y));
	}

	m_DirDef.x += m_CameraMove.x;
	m_DirDef.y += m_CameraMove.y;
	m_OffsetZ += m_CameraMove.z;
}