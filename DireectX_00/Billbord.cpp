#include "Billbord.h"
#include"Camera.h"

CBillbord::CBillbord()
{}
CBillbord::~CBillbord()
{}
void CBillbord::Init()
{}

void CBillbord::Update(D3DXMATRIX World)
{
	// ���[���h�s�񂩂���W�̔����o�� + �ݒ�
	billbox.Pos.x = World._41;
	billbox.Pos.y = World._42;
	billbox.Pos.z = World._43;
}

void CBillbord::Release(BillbordPlate *billbord)
{

	if (billbord->g_pD3DTextureBillboard != NULL)
	{// �e�N�X�`���̊J��
		billbord->g_pD3DTextureBillboard->Release();
		billbord->g_pD3DTextureBillboard = NULL;
	}

	if (billbord->g_pD3DVtxBuffBillboard != NULL)
	{// ���_�o�b�t�@�̊J��
		billbord->g_pD3DVtxBuffBillboard->Release();
		billbord->g_pD3DVtxBuffBillboard = NULL;
	}
	
}

void CBillbord::Render()
{
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	GetDxMgr()->GetDxDevice()->GetTransform(D3DTS_VIEW,&mtxView);

	// ���C�e�B���O�𖳌��ɂ���
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&billbox.g_mtxWorldBillboard);

	

	// �|���S���𐳖ʂɌ�����
#if 0
	// �t�s������߂�
	D3DXMatrixInverse(&g_mtxWorldBillboard[nNumb], NULL, &mtxView);
	g_mtxWorldBillboard[nNumb]._41 = 0.0f;
	g_mtxWorldBillboard[nNumb]._42 = 0.0f;
	g_mtxWorldBillboard[nNumb]._43 = 0.0f;
	//���s�ړ��������Ȃ���

#else
	// �]�u�s������߂�
	billbox.g_mtxWorldBillboard._11 = mtxView._11;
	billbox.g_mtxWorldBillboard._12 = mtxView._21;
	billbox.g_mtxWorldBillboard._13 = mtxView._31;

	billbox.g_mtxWorldBillboard._21 = 0.0f;
	billbox.g_mtxWorldBillboard._22 = 1.0f;
	billbox.g_mtxWorldBillboard._23 = 0.0f;

	billbox.g_mtxWorldBillboard._31 = mtxView._13;
	billbox.g_mtxWorldBillboard._32 = mtxView._23;
	billbox.g_mtxWorldBillboard._33 = mtxView._33;

#endif

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale, billbox.Size.x, billbox.Size.y, 1.0f);
	D3DXMatrixMultiply(&billbox.g_mtxWorldBillboard, &billbox.g_mtxWorldBillboard, &mtxScale);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, billbox.Pos.x, billbox.Pos.y, billbox.Pos.z);
	D3DXMatrixMultiply(&billbox.g_mtxWorldBillboard, &billbox.g_mtxWorldBillboard, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	GetDxMgr()->GetDxDevice()->SetTransform(D3DTS_WORLD, &billbox.g_mtxWorldBillboard);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	GetDxMgr()->GetDxDevice()->SetStreamSource(0, billbox.g_pD3DVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	GetDxMgr()->GetDxDevice()->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	GetDxMgr()->GetDxDevice()->SetTexture(0, billbox.g_pD3DTextureBillboard);

	// �|���S���̕`��
	GetDxMgr()->GetDxDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ���C���e�B���O��L���ɂ���
	GetDxMgr()->GetDxDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
}

HRESULT CBillbord::CreateMake3DBillbord(
	LPCTSTR  TexFile,
	float SizeX,
	float SizeY,
	float TexPosLeft,
	float TexPosRight,
	float TexPosUp,
	float TexPosDown)
{
	D3DXCreateTextureFromFile(GetDxMgr()->GetDxDevice(),						// �f�o�C�X�ւ̃|�C���^
		TexFile,			// �t�@�C���̖��O
		&billbox.g_pD3DTextureBillboard);	// �ǂݍ��ރ�����

	if (FAILED(GetDxMgr()->GetDxDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,						// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&billbox.g_pD3DVtxBuffBillboard,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	 {//���_�o�b�t�@�̒��g�𖄂߂�

		 // ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		 billbox.g_pD3DVtxBuffBillboard->Lock(0, 0, (void**)&billbox.vertex3d, 0);

		 // ���_���W�̐ݒ�
		 billbox.vertex3d[0].vtx = D3DXVECTOR3(-SizeX / 2, -SizeY / 2, 0.0f);
		 billbox.vertex3d[1].vtx = D3DXVECTOR3(-SizeX / 2, SizeY / 2, 0.0f);
		 billbox.vertex3d[2].vtx = D3DXVECTOR3(SizeX / 2, -SizeY / 2, 0.0f);
		 billbox.vertex3d[3].vtx = D3DXVECTOR3(SizeX / 2, SizeY / 2, 0.0f);

		 billbox.Size.x = SizeX;
		 billbox.Size.y = SizeY;

		 // �@���̐ݒ�
		 billbox.vertex3d[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		 billbox.vertex3d[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		 billbox.vertex3d[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		 billbox.vertex3d[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		 // ���ˌ��̐ݒ�
		 billbox.vertex3d[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		 billbox.vertex3d[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		 billbox.vertex3d[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		 billbox.vertex3d[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		 // �e�N�X�`�����W�̐ݒ�
		 billbox.vertex3d[0].tex = D3DXVECTOR2(TexPosLeft, TexPosUp);
		 billbox.vertex3d[1].tex = D3DXVECTOR2(TexPosRight, TexPosUp);
		 billbox.vertex3d[2].tex = D3DXVECTOR2(TexPosLeft, TexPosDown);
		 billbox.vertex3d[3].tex = D3DXVECTOR2(TexPosRight, TexPosDown);

		 // ���_�f�[�^���A�����b�N����
		 billbox.g_pD3DVtxBuffBillboard->Unlock();
	 }

	 return S_OK;

}