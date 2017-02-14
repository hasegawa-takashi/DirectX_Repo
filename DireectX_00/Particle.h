//#pragma once
//#include "Camera.h"
//#include"ObjManager.h"
//
//enum EParticleCoord {
//	eCartesian = 0,				// 直交座標系(x,y,z)
//	eSpherical,					// 球座標系(r,φ,θ)
//	eCylindrical,				// 円筒座標系(r,h,θ)
//
//	eMaxParticleCoord
//};
//
//struct TParticleParam
//{
//	EParticleCoord	coord;					// 座標系
//	float			fDuration;				// 生成周期
//	UINT			uMaxParticles;			// 最大パーティクル数
//	bool			bLooping;				// 繰り返し
//	bool			bUse;					// ON/OFF
//	float			fGravity;				// 重力加速度
//	float			fLowSpeed;				// 最低速度
//	float			fMaxSpeed;				// 最高速度
//	float			fAccelerator;			// 加速度
//	float			fMiniSize;				// 最低拡大率
//	float			fMaxSize;				// 最大拡大率
//	float			fLowRotate;				// 最低角度
//	float			fMaxRotate;				// 最大角度
//	D3DXCOLOR		LowColor;				// 初期カラー
//	D3DXCOLOR		MaxColor;				// 変化後の色
//	float			fMiniLife;				// 最低ライフ
//	float			fMaxLife;				// 最大ライフ
//	UINT			uRate;					// パーティクルの生成数
//	float			fCornAngle;				// コーン角度
//	float			fRadius;				// 半径
//	TCHAR			szTexFName[_MAX_PATH];	// テクスチャファイル名
//};
//
//class CParticle: public ObjBase
//{
//private:
//	LPDIRECT3DTEXTURE9	m_pTexture;
//	TCHAR				m_szTexFName[_MAX_PATH];	// テクスチャファイル名
//
//	TParticleParam		m_pp;
//	float				m_fTime;			// パーティクル生成時間
//	float				m_fRate;			// パーティクル生成数ワーク
//	UINT				m_uParticles;		// 残りパーティクル数
//
//	UINT		m_uUse;
//	struct TVertex {
//		D3DVECTOR	m_pos;
//		D3DVECTOR	m_normal;
//		D3DCOLOR	m_diffuse;
//		float		m_u, m_v;
//	};
//	TVertex*	m_pVertex;
//	WORD*		m_pIndex;
//
//public:
//	void SetParam(TParticleParam& pp);
//
//	//===================================
//	//
//	//		ここから先、継承分
//	//
//	CParticle();				// コンストラクタ
//	virtual ~CParticle(void);	// デストラクタ//
//
//	void Init();				// 初期化
//	void Update();				// 更新
//	void LateUpdate() {}		// あとから更新
//	void Draw();				// 描画
//	void LateDraw();			// 透過描画
//	void UIDraw() {}			// UI描画
//	void Release();				// リリース
//	void Pause() {}				// ポーズ画面
//	bool AllRelaseObj() {}		// 終了用
//
//	ColBox GetCol() { return Collision; }
//	CMeshRender* GetRender() { return m_ModelMesh; }
//	void SetidentNumb(int Numb) { ObjNumb = Numb; }
//	void SetPos(D3DXVECTOR3 pos);
//	virtual D3DXVECTOR3 GetPos() { return m_Pos; }
//
//private:
//	void UpdateTexture(void);
//
//	//===================================
//	//
//	//		プライベート変数
//	//
//	ColBox Collision;			// 当たり判定用
//
//};