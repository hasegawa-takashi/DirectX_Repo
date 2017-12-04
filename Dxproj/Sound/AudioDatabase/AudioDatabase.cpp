#include "AudioDatabase.h"


CAudioDatabase::CAudioDatabase()
{
}

// 終了処理
CAudioDatabase::~CAudioDatabase()
{
	DeleteSoundData();
}

//-----------------------------------------------------------------
//
//	LoadResourceFile
//		リソースファイルのロード
//
void CAudioDatabase::SetVoiceCue(std::string name, AudioElement* voice)
{
	// Cueデータの作成
	CSoundCue soundcue;
	soundcue.Registervoice(voice);
	m_Cuemap.insert( std::make_pair(name, soundcue) );
}

void CAudioDatabase::PopVoiceCue(std::string name, AudioElement* voice)
{
	// Cueデータの作成
	m_Cuemap[name].UnRegistervoice(voice);
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

	// Dictionaryの削除
	m_Cuemap.clear();
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
//		Bug :: ここでのコピーが分離していないために同時に音が鳴るとバグが発生している可能性
//
void CAudioDatabase::SetAudioSource(AudioElement* audioelement, std::string type ,std::string name, VoiceCallback* voiceCallback)
{
	// Wave情報を外部リースから読み込んで取得
	audioelement->Waveformatdata = new CWaveformatData(type,name);
	audioelement->Soundelemt = audioelement->Waveformatdata->GetWaveElement();

	// マスターボイスへの登録
	GetXAudio2Mgr()->SetXAudio2SourceVoice( &(audioelement)->RegistVoice , *(audioelement)->Soundelemt.Waveformat, voiceCallback);

	// 種類別に登録
	m_Cuemap[type].Registervoice(audioelement);

	// 音量の設定
	(audioelement)->RegistVoice->SetVolume(audioelement->Soundelemt.MaxVolume);
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

	m_Cuemap[name].ChangeVolume(volume);
}