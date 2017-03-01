#include "Camera.h"
#include"Input.h"
#include<math.h>
#include"MeshRender.h"
#include"Debug.h"
#include"Calculation.h"

///////////////////////////////////////////////////////////////////////////////////////
//
//	カメラのコンストラクタ
//
CCamera::CCamera()
{
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixIdentity(&m_mtxProjection);
	D3DXMatrixIdentity(&m_camPoseMat);
	
	m_lookAt = VECZERO;
	m_Pos	 = D3DXVECTOR3(0, 3, -5);
	m_DirDef = VECZERO;
	m_Upvec  = D3DXVECTOR3(0, 1, 0);

	m_fFovy = D3DXToRadian(FOVY);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_fZNear = NEAR_CLIP;
	m_fZFar = FAR_CLIP;
	
	m_isNeedUpdate = true;
	m_CamType = Cam_TPVIEW;

	m_camZrot = 0.0f;
	m_offsetZ = 0.0f;
	m_Distance = 1.0f;
	m_camAngleUnit = 0.1f;
	m_CorrectionVal = D3DXVECTOR3(0, 0, 1);

	ObjNumb = GetObjMgr()->RenameObj(ID_CAMERA, ObjID);
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	カメラのデストラクタ
//
CCamera::~CCamera()
{

}

///////////////////////////////////////////////////////////////////////////////////////
//
//	カメラの初期化
//
void CCamera::Init()
{
	CObjManager::Instance()->SerchObj(ID_PLAYER, Master);
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	カメラの更新
//
void CCamera::LateUpdate()
{

	// デバック項目
	if (CInput::GetKeyTrigger(DIK_1)) {
		m_CamType = Cam_FPVIEW;
	}
	if (CInput::GetKeyTrigger(DIK_2)) {
		m_CamType = Cam_TPVIEW;
	}
	if (CInput::GetKeyTrigger(DIK_3)) {
		m_CamType = Cam_PREVIEW;
	}

	// カメラ移動
	CameraInput();

	// カメラView更新
	switch (m_CamType)
	{
	case Cam_FPVIEW:
		FPSCamera();
		break;
	case Cam_TPVIEW:
		TPSCamera();
		break;
	case Cam_PREVIEW:
		PreviewCamera();
		break;
	default:
		break;
	}



}

///////////////////////////////////////////////////////////////////////////////////////
//
//	カメラの描画関係
//
void CCamera::Draw()
{
	CameraMove();

	// ビュー行列の更新
	UpdateViewMat();

	D3DXMatrixLookAtLH(&m_mtxView,&NowPos,&m_lookAt,&m_Upvec);
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, m_fFovy, m_fAspect, m_fZNear, m_fZFar);

	GetDxMgr()->GetDxDevice()->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
	GetDxMgr()->GetDxDevice()->SetTransform(D3DTS_VIEW, &m_mtxView);
	
	m_Move = VECZERO;
	m_CameraMove = VECZERO;
	

	//カメラデバック
	CDebug::Instance()->Conversion(_T("\nCameraPos"), NowPos);
	CDebug::Instance()->Conversion(_T("\n注視点"), m_lookAt);


	// 数値の初期化
	OffSetVar();
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	カメラの移動更新
//
void CCamera::CameraInput()
{
	// カメラの制御
	if (CInput::GetMouseAxis(MOUSE_X)) {
		m_CameraMove.x -= (CInput::GetMouseAxis(MOUSE_X) );
	}

	if (CInput::GetMouseAxis(MOUSE_Y)) {
		m_CameraMove.y -= (CInput::GetMouseAxis(MOUSE_Y) );
	}

	// 回転移動分
	m_DirDef.x += m_CameraMove.x;
	m_DirDef.y += m_CameraMove.y;
	m_offsetZ += m_CameraMove.z;
	
	m_isNeedUpdate = true;

}

///////////////////////////////////////////////////////////////////////////////////////
//
//	二つのベクトルの角度を求める
//
double CCamera::AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B)
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

///////////////////////////////////////////////////////////////////////////////////////
//
//	FPカメラ
//
void CCamera::FPSCamera()
{

	if (m_isNeedUpdate == false) {
		// 更新の必要無し
		return;
	}
	
	m_OldPos = m_Pos;
	m_Pos = Master.begin()->second->GetPos();

}

///////////////////////////////////////////////////////////////////////////////////////
//
//	球面束縛カメラ
//
void CCamera::TPSCamera()
{
	// 更新確認
	if (m_isNeedUpdate == false) {
		return;
	}

	// カメラをZ軸回転で姿勢行列
	D3DXMATRIX mtxZrot;
	D3DXMatrixRotationZ(&mtxZrot, m_camZrot);
	m_camPoseMat = mtxZrot *m_camPoseMat;

	// 緯度経度の差分移動
	m_camPoseMat._21 = 0.0f;
	m_camPoseMat._22 = 1.0f;
	m_camPoseMat._23 = 0.0f;

	D3DXVECTOR3 DL;
	D3DXVec3TransformCoord(&DL,&m_DirDef,&m_camPoseMat);

	D3DXVECTOR3 RotAxis;

	D3DXVECTOR3* camZAxis = (D3DXVECTOR3*)m_camPoseMat.m[2];
	D3DXVec3Cross(&RotAxis, &DL, camZAxis);
	
	D3DXQUATERNION TransQ;
	D3DXQuaternionRotationAxis(&TransQ,&RotAxis,m_camAngleUnit);

	D3DXMATRIX TransRotMat;
	D3DXMatrixRotationQuaternion(&TransRotMat,&TransQ);
	D3DXVec3TransformCoord(&m_Pos,&m_Pos,&TransRotMat);

	// 移動後のカメラ姿勢の更新
	D3DXVECTOR3 X, Y, Z;

	Z = -m_Pos;
	D3DXVec3Normalize(&Z, &Z);

	memcpy(&Y,m_camPoseMat.m[1],sizeof(D3DXVECTOR3));
	D3DXVec3Cross(&X,&Y,&Z);
	D3DXVec3Normalize(&X,&X);

	D3DXVec3Cross(&Y, &Z, &X);
	D3DXVec3Normalize(&Y, &Y);

	D3DXMatrixIdentity(&m_camPoseMat);
	memcpy(m_camPoseMat.m[0], &X, sizeof(D3DXVECTOR3));
	memcpy(m_camPoseMat.m[1], &Y, sizeof(D3DXVECTOR3));
	memcpy(m_camPoseMat.m[2], &Z, sizeof(D3DXVECTOR3));

	// 奥行きの設定
	ZDistRenge();

}

///////////////////////////////////////////////////////////////////////////////////////
//
//	奥行きの設定
//
void CCamera::ZDistRenge()
{
	// 奥行きの更新
	m_Distance = D3DXVec3Length(&m_Pos);
	if (m_Distance - m_offsetZ > 0) {
		D3DXVECTOR3 Z = -m_Pos;
		D3DXVec3Normalize(&Z, &Z);
		m_Pos += m_offsetZ * Z;
		m_Distance -= m_offsetZ;
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	ビュー行列の更新
//
void CCamera::UpdateViewMat()
{
	// ビュー行列の更新
	D3DXVECTOR3 posW = m_Pos + m_lookAt;
	memcpy(&m_mtxView, &m_camPoseMat, sizeof(D3DXMATRIX));
	memcpy(&m_mtxView.m[3], &posW, sizeof(D3DXVECTOR3));
	m_mtxView._44 = 1.0f;
	D3DXMatrixInverse(&m_mtxView, 0, &m_mtxView);
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	固定カメラ
//
void CCamera::PreviewCamera()
{
	// カメラの固定ポジション
	NowPos = m_Pos;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	カメラのZ回転
//
void CCamera::RotZ(float radian) {

	if (radian == 0.0f) {
		return;	// 変更されていない
	}

	m_camZrot = radian;
	m_isNeedUpdate = true;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	カメラの注視点の設定
//
void CCamera::SetLookAt(D3DXVECTOR3 look)
{
	m_lookAt = look;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	カメラの注視点の設定
//
void CCamera::SetLookAt(D3DXVECTOR3 lookAt , D3DXVECTOR3 Correct )
{
	m_lookAt = lookAt + Correct;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	カメラのPosの設定
//
void CCamera::SetPos(D3DXVECTOR3 Pos)
{
	m_Pos = Pos;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	ステータスの初期化
//
void CCamera::OffSetVar()
{
	memset(&m_DirDef, 0, sizeof(D3DXVECTOR3));
	m_offsetZ = 0;
	m_camZrot = 0;
	m_isNeedUpdate = false;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	カメラの追従移動
//
void CCamera::CameraMove()
{
	// 平行移動分
	if (!Master.empty())
	{
		m_Move = Master.begin()->second->GetPos();
		D3DXVECTOR3 LookatPos = Master.begin()->second->GetPos();
		// 補正
		float ForVec = m_DirDef.z * 1.5f; // カメラの向き
		m_lookAt = LookatPos + (D3DXVECTOR3(0.0f, -ForVec, -1.5f));
		//m_lookAt = LookatPos;
		NowPos = m_Pos + m_Move;
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//
//	カメラのY軸固定の
//
D3DXMATRIX CCamera::GetZVec()
{
	D3DXMATRIX Out;
	D3DXMatrixIdentity(&Out);
	CCalculation::CalcLookAtMatrixFix(&Out,&NowPos,&m_lookAt,&m_Upvec);

	return Out;

}