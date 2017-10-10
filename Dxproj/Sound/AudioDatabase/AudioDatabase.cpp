#include "AudioDatabase.h"


CAudioDatabase::CAudioDatabase()
{
}

// 終了処理
CAudioDatabase::~CAudioDatabase()
{
	DeleteSoundData();
	CloseResourceFile();
}

//-----------------------------------------------------------------
//
//	LoadResourceFile
//		リソースファイルのロード
//
void CAudioDatabase::LoadResourceFile(std::string name)
{
	// Csvの読み込み。
	CWaveformatData* waveformatdata = new CWaveformatData(name);

	// 登録をする。
	m_Waveformat.insert( std::make_pair(name,waveformatdata) );
	
	// Cueデータの作成
	CSoundCue* soundcue = new CSoundCue();
	m_Cuemap.insert( std::make_pair(name, soundcue) );

	

}

//-----------------------------------------------------------------
//
//	DeleteSoundData
//		保持しているSourceVoiceの削除
//
void CAudioDatabase::DeleteSoundData()
{
	if (m_Cuemap.empty())
		return;

	// 全Wavedataの削除
	for each (auto var in m_Cuemap)
	{
		delete var.second;
	}

	// Dictionaryの削除
	m_Cuemap.clear();
}

//-----------------------------------------------------------------
//
//	CloseResourceFile
//		読み込んだリソースフォルダの開放
//
void CAudioDatabase::CloseResourceFile()
{
	if (m_Waveformat.empty())
		return;

	// 全Wavedataの削除
	for each (auto var in m_Waveformat)
	{
		delete var.second;
	}

	// Dictionaryの削除
	m_Waveformat.clear();

}

//-----------------------------------------------------------------
//
//	SetListener
//		リスナーの登録
//
void CAudioDatabase::SetListener(D3DXMATRIX* listener)
{
	CX3DSound::Instance()->SetListener(listener);
}

//-----------------------------------------------------------------
//
//	SetAudioSource
//		再生音源の登録
//		ここで生成した情報を各種ポインタに持たせて再生させたい		
//
void CAudioDatabase::SetAudioSource(AudioElement** audioelement, std::string type ,std::string name)
{

	if (m_Waveformat.empty())
	{
		return;
	}

	// Wave情報の取得
	(*audioelement)->Soundelemt = m_Waveformat[type]->GetWaveElement(name);

	// マスターボイスへの登録
	GetXAudio2Mgr()->SetXAudio2SourceVoice( &(*audioelement)->RegistVoice , *(*audioelement)->Soundelemt.Waveformat);

	// 種類ごとにSourceボイスの登録
	m_Cuemap[type]->Registervoice(*audioelement);
}

//-----------------------------------------------------------------
//
//	ChangeVolume
//		種類ごとのボリュームの変更
//
void CAudioDatabase::ChangeCueVolume(std::string name, float volume)
{
	if (m_Cuemap.empty())
		return;

	m_Cuemap[name]->ChangeVolume(volume);
}