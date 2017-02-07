#pragma once

#include"ObjManager.h"
#include"Window.h"



#define VECZERO D3DXVECTOR3(0,0,0)
//////////////////////////////////
//		現在のカメラの状態
//////////////////////////////////
enum CamState
{
	Cam_FPVIEW = 0,
	Cam_TPVIEW,
	Cam_PREVIEW,

	MAX_VIEW
};

//////////////////////////////////////////////////////////////
//
//		Camara
//			ゲーム内カメラのクラス
//				球面カメラとFPSカメラを作らなきゃいけないことに気付いた
//
/////////////////////////////////////////////////////////////

class CCamera : public ObjBase
{

public:

	//---------------------------------------
	// カメラのデストラクタ
	~CCamera();

	//---------------------------------------
	// カメラのコンストラクタ
	CCamera();

	//---------------------------------------
	// カメラのインスタンス
	/*static CCamera* Instance(){
		static CCamera _Instance;
		return &_Instance;
	}*/

	//----------------------------
	// --- オブジェクトの初期化
	void Init();
	//----------------------------
	// --- オブジェクトの更新
	void Update();
	//----------------------------
	// --- オブジェクトの描画
	void Draw();
	//----------------------------
	// --- オブジェクトの削除
	void Release();
	//----------------------------
	// --- ポーズ画面
	void Pause(){};
	//----------------------------
	// --- 表示画面
	void UIDraw(){};
	//----------------------------
	// --- 最終処理全削除用
	bool AllRelaseObj(){ return true; };

	//---------------------------------------
	// カメラの座標の取得
	D3DXVECTOR3 GetCameraPos();

	//---------------------------------------
	// カメラの向き
	D3DXMATRIX GetCameraView()
	{
		return m_mtxView;
	}

	//---------------------------------------
	// カメラの移動更新
	void CameraMove();
	
	//---------------------------------------
	// カメラの注視点の設定
	void SetLookAt(D3DXVECTOR3 look);

	//---------------------------------------
	// カメラのZ回転
	void RotZ(float radian);

	//----------------------------------------
	// --- オブジェクトの更新(あとから用)
	void LateUpdate();

	//----------------------------------------
	// --- オブジェクトの描画(あとから用)
	void LateDraw();

	//----------------------------------------
	// --- コリジョンの設定
	ColBox GetCol();

	//----------------------------------------
	// --- View行列の取得
	D3DXVECTOR3 GetView();

	//----------------------------------------
	// --- カメラタイプの設定
	void SetCameraType(int Type);

	//----------------------------------------
	// --- Posの取得
	void SetPos(D3DXVECTOR3 Pos);

private:

	//---------------------------------------
	// FPSカメラ
	void FPSCamera();

	//---------------------------------------
	// 球面束縛カメラ
	void TPSCamera();

	//---------------------------------------
	// タイトル等のカメラが動かない用
	void PreviewCamera();

	//---------------------------------------
	// クオータニオン→行列計算
	void QuaternionToMatrix();

	//---------------------------------------
	// 行列計算→クオータニオン
	void MatrixToQuaternion();

	//---------------------------------------
	// ベクトル間の角度を算出
	double AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B);

	// --- ここから変数宣言 --- //
	int m_CamType;
	int ObjNumb;
	bool m_isNeedUpdate;			// 更新した？

	D3DXVECTOR3 m_OldPos;

	D3DXVECTOR3	m_lookAt;			// 注視点
	D3DXVECTOR3 m_Move;				// 移動方向
	D3DXVECTOR3 m_DirDef;			// カメラの向き
	D3DXVECTOR3 m_Upvec;			// 上

	D3DXVECTOR3 NowPos;				// 現在座標
	D3DXVECTOR3 NowRot;				// 現在の回転値

	D3DXVECTOR3 m_CameraMove;		// 速度

	D3DXVECTOR3 m_CorrectionVal;	// lookatの補正値

	float m_Distance;				// カメラと注視点の距離
	float m_camZrot;				// カメラZ軸での回転差分
	float m_camAngleUnit;			// 移動時の回転単位
	float m_offsetZ;				// オフセット値

	float		m_fFovy;	// 視野角
	float		m_fAspect;	// アスペクト比
	float		m_fZNear;	// 前方クリップ距離
	float		m_fZFar;	// 後方クリップ距離

	D3DXMATRIX	m_mtxView;			// ビューマトリクス
	D3DXMATRIX	m_mtxProjection;	// プロジェクションマトリクス
	D3DXMATRIX	m_camPoseMat;		// カメラの姿勢行列

	ColBox Collision;				// 当たり判定用

	OBJMGR Master;



};

