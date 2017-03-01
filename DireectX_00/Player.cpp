#include"Player.h"
#include"Input.h"
#include"RenderMgr.h"
#include"Scene.h"
#include"Calculation.h"

// �萔�錾
#define DEFINE_VEC3 D3DXVECTOR3(0,0,0)
#define ROLLSPEED (0.001f)

#define PATH_MESHPLAYER	_T("../data/model/Player.x")
#define PATH_PARTICLE_1	_T("../data/Texture/Spark.png")

////////////////////////////////////////////////////////////////////////
//
//		�R���X�g���N�^
//
////////////////////////////////////////////////////////////////////////
Player::Player()
{

	// �ϐ�������
	m_Pos = D3DXVECTOR3(0, 0, 0);
	m_Dir = 0.0f;
	//m_CameraMove = DEFINE_VEC3;
	m_Speed = 0.3f;
	m_Dash = 0.2f;
	m_Step = 1.0;

	m_Jump = false;
	m_Move = false;
	m_dAnimTime = 0.0;
	HitCnt = false;
	BalletCnt = 0;

	m_ModelMesh = new CMeshRender;

	if (!m_Load)
	{
		m_Load = m_ModelMesh->Initialize(PATH_MESHPLAYER);

		if (m_Load)
		{
			m_ModelMesh->SwitchAnimSet(1);
		}
	}

	D3DXMatrixIdentity(&m_mtxWorld);

	m_mtxWorld._41 = m_Pos.x;
	m_mtxWorld._42 = m_Pos.y;
	m_mtxWorld._43 = m_Pos.z;

	Collision.m_Pos = m_Pos + D3DXVECTOR3(0, 1.0f, 0);

	Collision.m_fLength[0] = 0.5f;
	Collision.m_fLength[1] = 1.5f;
	Collision.m_fLength[2] = 0.3f;

	// �e�̏�����
	CBallet Ballet;
	// �e�����������ف`
	for (size_t i = 0; i < MAX_BALLET; i++)
	{
		_vecbullet_L.push_back(Ballet);
	}
	
}

////////////////////////////////////////////////////////////////////////
//
//		�f�X�g���N�^
//
////////////////////////////////////////////////////////////////////////
Player::~Player()
{
}

////////////////////////////////////////////////////////////////////////
//
//		�v���C���[������
//
////////////////////////////////////////////////////////////////////////
void Player::Init()
{
	// �v���C���[�̂Ȃ܂������@
	ObjNumb = CObjManager::Instance()->RenameObj(ID_PLAYER,ObjID);

	// �J�����I�u�W�F�N�g�̎擾�B
	// �^�L���X�g�ɂĖ������ϊ��������Ă���B
	// ���܂肢�����@�ł͂Ȃ��Ǝv���̂ł��܂���Ȃ��悤�ɒ��ӂ���ׂ�( ߄D�)
	CObjManager::Instance()->SerchObj(ID_CAMERA, CameraObjMgr);
	ObjBase* hoge = CameraObjMgr.begin()->second;
	CameraObj = dynamic_cast<CCamera*>(hoge);
	
	// �e�̏�����
	for (auto itr = _vecbullet_L.begin(); itr != _vecbullet_L.end(); ++itr )
	{
		itr->Init();
	}


	CObjManager::Instance()->LateRenderPush(this);
}

////////////////////////////////////////////////////////////////////////
//
//		�v���C���[�̍X�V����
//
////////////////////////////////////////////////////////////////////////
void Player::Update()
{
	// �ړ��X�V
	Move();
	
	// �ˌ����͎ˌ�
	Shot();

	// �����̍X�V
	ChangeTPSDir();

	// �L�����̈ړ�
	m_Pos.x = m_mtxWorld._41 -= (m_mtxWorld.m[2][0] * m_MoveSpeed.z);
	m_Pos.y = m_mtxWorld._42 -= (m_mtxWorld.m[2][1] * m_MoveSpeed.z);
	m_Pos.z = m_mtxWorld._43 -= (m_mtxWorld.m[2][2] * m_MoveSpeed.z);
	
	// ���Ƃ̈ړ�����
	CheckFloor();
	
	// �A�j���[�V�������b�V���̍X�V
	m_ModelMesh->Update(m_mtxWorld);
	
	// �e�̍X�V
	for (auto itr = _vecbullet_L.begin(); itr != _vecbullet_L.end(); ++itr)
	{
		itr->Update();
	}

	// ����Ȃ��́I
	Reset();

}

////////////////////////////////////////////////////////////////////////
//
//		�v���C���[�̕`��
//
////////////////////////////////////////////////////////////////////////
void Player::Draw()
{

	//D3DXMatrixRotationYawPitchRoll();

	// �L�����N�^�[�̕`��
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_SPECULARENABLE, FALSE);	// ���ʔ��˂𖳌�
	m_ModelMesh->Render();
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	// �e�̕`��
	for (auto itr = _vecbullet_L.begin(); itr != _vecbullet_L.end(); ++itr)
	{
		if (itr->GetShotFlag())
			continue;
		itr->LateDraw();
	}

}

void Player::LateDraw(){}
void Player::UIDraw(){}

////////////////////////////////////////////////////////////////////////
//
//	�v���C���[�̏I������	
//
////////////////////////////////////////////////////////////////////////
void Player::Release()
{
	// ���b�V���̏I������
	if (m_Load)
	{
		m_ModelMesh->Finalize();
		delete m_ModelMesh;
		m_Load = false;
	}

	// �e�̏I������
	if (!_vecbullet_L.empty())
	{
		_vecbullet_L.clear();
	}
}

////////////////////////////////////////////////////////////////////////
//		
//	�ړ�����
//
////////////////////////////////////////////////////////////////////////
void Player::Move()
{

	float MoveSpeed = 0;	// �ړ���

	// �_�b�V������
	if (CInput::GetKeyPress(DIK_LSHIFT))
	{
		MoveSpeed += m_Dash;
	}

	if (CInput::GetKeyTrigger(DIK_SPACE))
	{
		MoveSpeed += m_Step;
	}

	// �ړ�����
	if (CInput::GetKeyPress(DIK_RIGHT) || CInput::GetKeyPress(DIK_D) ||
		CInput::GetKeyPress(DIK_LEFT) || CInput::GetKeyPress(DIK_A) ||
		CInput::GetKeyPress(DIK_UP) || CInput::GetKeyPress(DIK_W) ||
		CInput::GetKeyPress(DIK_DOWN) || CInput::GetKeyPress(DIK_S))
	{
		// �ړ�����
		if (CInput::GetKeyPress(DIK_RIGHT) || CInput::GetKeyPress(DIK_D))
		{
			m_Dir = 90.0f;
		}
		if (CInput::GetKeyPress(DIK_LEFT) || CInput::GetKeyPress(DIK_A)) {
			m_Dir = -90.0f;
		}
		if (CInput::GetKeyPress(DIK_UP) || CInput::GetKeyPress(DIK_W)) {
			m_Dir = 0.0f;
		}
		if (CInput::GetKeyPress(DIK_DOWN) || CInput::GetKeyPress(DIK_S)) {
			m_Dir = 180.0f;
		}

		if ( (CInput::GetKeyPress(DIK_RIGHT) || CInput::GetKeyPress(DIK_D)) &&
			(CInput::GetKeyPress(DIK_UP) || CInput::GetKeyPress(DIK_W)) )
		{
			m_Dir = 45.0f;
		}

		if ((CInput::GetKeyPress(DIK_RIGHT) || CInput::GetKeyPress(DIK_D)) &&
			(CInput::GetKeyPress(DIK_DOWN) || CInput::GetKeyPress(DIK_S))) {
			m_Dir = 135.0f;
		}

		if ((CInput::GetKeyPress(DIK_LEFT) || CInput::GetKeyPress(DIK_A)) &&
			(CInput::GetKeyPress(DIK_DOWN) || CInput::GetKeyPress(DIK_S))) {
			m_Dir = 225.0f;
		}

		if ((CInput::GetKeyPress(DIK_LEFT) || CInput::GetKeyPress(DIK_A)) &&
			(CInput::GetKeyPress(DIK_UP) || CInput::GetKeyPress(DIK_W)) ) {
			m_Dir = -45.0f;
		}

		m_MoveSpeed.z += (m_Speed + MoveSpeed);
		m_Move = true;

	}
	else{
		m_Move = false;
	}

	

}

////////////////////////////////////////////////////////////////////////
//		
//	�{�[���̉�]
//
////////////////////////////////////////////////////////////////////////
void Player::TransBorn()
{
	D3DXMATRIX* HipBorn = m_ModelMesh->SerchBorn("root_spine_02");


	D3DXMATRIX rot;
	D3DXVECTOR3 YVec = D3DXVECTOR3(HipBorn->_21, HipBorn->_22, HipBorn->_23);
	D3DXVECTOR3 XVec = D3DXVECTOR3(HipBorn->_11, HipBorn->_12, HipBorn->_13);
	D3DXVECTOR3 ZVec = D3DXVECTOR3(HipBorn->_31, HipBorn->_32, HipBorn->_33);


	D3DXMatrixRotationZ(&rot, D3DXToRadian(0));
	D3DXVec3TransformCoord(&XVec, &XVec, &rot);

	D3DXVec3Cross(&ZVec, &XVec, &YVec);
	D3DXVec3Normalize(&ZVec, &ZVec);
	D3DXVec3Cross(&XVec, &YVec, &ZVec);
	D3DXVec3Normalize(&XVec, &XVec);

	XVec *= 0.01f;
	ZVec *= 0.01f;

	memcpy(HipBorn->m[0], &XVec, sizeof(D3DXVECTOR3));
	memcpy(HipBorn->m[2], &-ZVec, sizeof(D3DXVECTOR3));

}

////////////////////////////////////////////////////////////////////////
//		
//	�ˌ�����(������̏���)
//
////////////////////////////////////////////////////////////////////////
void Player::Shot()
{
	// �e������
	if (CInput::GetMousePress(0))
	{
		for (auto itr = _vecbullet_L.begin(); itr != _vecbullet_L.end(); ++itr)
		{
			if (!itr->GetShotFlag())
				continue;
			itr->CreateBallet(balletpram_L);

		}
	}

	if (CInput::GetKeyPress(DIK_E)) {

		for (auto itr = _vecbullet_L.begin(); itr != _vecbullet_L.end(); ++itr)
		{
			BalletCnt = 0;

			itr->Reload();
		}

	}
}

////////////////////////////////////////////////////////////////////////
//		
//	�^�Q�j�󐔂ɂ��ړI�̈ȍ~
//	����ǂ����ɈڐA����ׂ�
//
////////////////////////////////////////////////////////////////////////
void Player::LastRun()
{
	/*if (HitCnt < MAX_BOT)
	{
		for (size_t i = 0; i < MAX_BALLET; i++)
		{
			if (Ballet[i].GetHitCheck())
				HitCnt++;
		}
	}
	else if (CObjManager::Instance()->CollisonCheck(ID_GOAL, COL_OBB, Collision))
	{

		CSceneMgr::Instance()->ChangeScene(new CEnd);
	}
	
	if (m_Pos.y < -10)
	{

		CSceneMgr::Instance()->ChangeScene(new CEnd);
	}*/
}

////////////////////////////////////////////////////////////////////////
//		
//	�v���C���[�̌�����ς���X�V����
//	ACT�p
////////////////////////////////////////////////////////////////////////
void Player::ChangeACTDir()
{
	if (m_Move)
	{
		if (m_Load)
		{
			m_ModelMesh->SwitchAnimSet(0);
		}

		// �v���C���[�̌����̐ݒ�
		D3DXMATRIX rot;
		D3DXVECTOR3 View;

		View = (m_Pos - CameraObj->GetPos());

		D3DXMatrixRotationY(&rot, D3DXToRadian(m_Dir));
		D3DXVec3TransformCoord(&View, &View, &rot);

		D3DXVECTOR3 ZVec = View;
		D3DXVECTOR3 YVec = m_mtxWorld.m[1];
		D3DXVECTOR3 XVec;

		D3DXVec3Cross(&XVec, &ZVec, &YVec);
		D3DXVec3Normalize(&XVec, &XVec);
		D3DXVec3Cross(&ZVec, &YVec, &XVec);
		D3DXVec3Normalize(&ZVec, &ZVec);

		memcpy(m_mtxWorld.m[0], &XVec, sizeof(D3DXVECTOR3));
		memcpy(m_mtxWorld.m[2], &-ZVec, sizeof(D3DXVECTOR3));

		// �ǂ̔���
		Collision.m_Pos.x = (m_Pos.x + 0.0f);
		Collision.m_Pos.y = (m_Pos.y + 1.0f);
		Collision.m_Pos.z = (m_Pos.z + 0.0f);

		Collision.Ray = ZVec;

		m_NowDir = ZVec;

		if (CObjManager::Instance()->CollisonCheck(ID_FIELD, COL_RAY, Collision))
		{
			D3DXVECTOR3 in = Collision.m_Pos - Collision.ResultPos;
			FLOAT out = D3DXVec3Length(&in);
			if (out < 0.5f)
			{
				m_Pos.z = m_mtxWorld._43 = Collision.ResultPos.z;
				m_MoveSpeed = DEFINE_VEC3;
			}
		}

	}
	else{
		if (m_Load)
		{
			m_ModelMesh->SwitchAnimSet(1);
		}
	}

}

////////////////////////////////////////////////////////////////////////
//		
//	�v���C���[�̌�����ς���X�V����
//	TPS�p
////////////////////////////////////////////////////////////////////////
void Player::ChangeTPSDir()
{
	D3DXMATRIX dir = CameraObj->GetZVec();

	

}

////////////////////////////////////////////////////////////////////////
//		
//	���Ƃ̂����蔻�����鏈��
//
////////////////////////////////////////////////////////////////////////
void Player::CheckFloor()
{
	// ���̐ݒ�
	Collision.m_Pos.x = (m_Pos.x + 0.0f);
	Collision.m_Pos.y = (m_Pos.y + 3.0f);
	Collision.m_Pos.z = (m_Pos.z + 0.0f);

	Collision.Ray.x = 0.0f;
	Collision.Ray.y = -1.0f;
	Collision.Ray.z = 0.0f;

	if (CObjManager::Instance()->CollisonCheck(ID_FIELD, COL_RAY, Collision))
	{
		m_Pos.y = m_mtxWorld._42 = Collision.ResultPos.y;
	}
	else{
		m_mtxWorld._42 -= 0.1f;
	}
}

////////////////////////////////////////////////////////////////////////
//		
//	�ϐ����Z�b�g
//
////////////////////////////////////////////////////////////////////////
void Player::Reset()
{
	// �����̏�����
	m_MoveSpeed = DEFINE_VEC3;
	Collision.WorldMtx = m_mtxWorld;
}