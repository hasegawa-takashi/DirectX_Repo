#pragma once
#include "Camera.h"
#include"ObjManager.h"

// Effecseer�֌W�̐ݒ�	
#include "..\data\Effecseer\include\Effekseer.h"
#include "..\data/Effecseer/include/EffekseerRendererDX9.h"
#include "..\data/Effecseer/include/EffekseerSoundXAudio2.h"
#if _DEBUG
#pragma comment(lib, "data/Effecseer/VS2015/Debug/Effekseer.lib" )
#pragma comment(lib, "data/Effecseer/VS2015/Debug/EffekseerRendererDX9.lib" )
#pragma comment(lib, "data/Effecseer/VS2015/Debug/EffekseerSoundXAudio2.lib" )
#pragma comment(lib, "data/Effecseer/VS2015/Debug/xaudio2.lib" )
#else
#pragma comment(lib, "data/Effecseer/VS2015/Release/Effekseer.lib" )
#pragma comment(lib, "data/Effecseer/VS2015/Release/EffekseerRendererDX9.lib" )
#pragma comment(lib, "data/Effecseer/VS2015/Release/EffekseerSoundXAudio2.lib" )
#pragma comment(lib, "data/Effecseer/VS2015/Debug/xaudio2.lib" )
#endif


class CParticle :public ObjBase
{
private:
	::Effekseer::Manager*			g_manager = NULL;
	::EffekseerRenderer::Renderer*	g_renderer = NULL;
	::EffekseerSound::Sound*		g_sound = NULL;
	::Effekseer::Effect*			g_effect = NULL;
	::Effekseer::Handle				g_handle = -1;
	::Effekseer::Vector3D			g_position;

public:

	CParticle() {}
	virtual ~CParticle() {}

	// === �p�����郁�b�Z�[�W === //

	// ���ꂼ��̍X�V�����̂��ߕK�{
	void Init() {};
	void Update() ;
	void LateUpdate() {};
	void Draw();
	void LateDraw();
	void UIDraw() {};
	void Release();
	void Pause() {};
	bool AllRelaseObj() {};

	// ��������\�����������
	ColBox GetCol() = 0;

	// ��̌ŗL�ł������
	CMeshRender GetRender() { return m_ModelMesh; }
	void SetidentNumb(int ID) { ObjNumb = ID; }
	int GetidentNumb() { return ObjNumb; }
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }
	D3DXVECTOR3 GetPos() { return m_Pos; }


};