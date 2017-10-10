#include "WaveformatData.h"

//====================================================
//	@fn
//	指定Csvの読み込み
//	@param filepath csvファイルの名前	
//
CWaveformatData::CWaveformatData(std::string filepath)
{
	RegistWaveformat(filepath);
}

//====================================================
//	@fn
//	登録されたWAVEFORMATEX情報の削除
//
CWaveformatData::~CWaveformatData()
{
	for each (auto var in m_Formatlist)
	{
		delete(var.Loadsoundfile);
	}

	m_Formatlist.clear();

}

//====================================================
//  @fn
//	外部リソースをWAVEFORMATEXに登録するための処理
//	@param filepath csvのファイル名を記入する
//
void CWaveformatData::RegistWaveformat(std::string filepath)
{

	// CSVファイルの読み込み
	std::ifstream ifs( m_cAudioPath + filepath + ".csv");
	
	if (!ifs)
	{
		printf(".csvファイルの読み込みに失敗しました");
		return;
	}

	// CSVの読み込み
	std::string str;

	getline(ifs, str);//不要部分の読み込み
	
	while (getline(ifs, str))
	{
		SoundElement dataelement;

		std::string audiotype, name, resourcetype, looptype, streamtype, maxvolume;
		std::istringstream stream(str);

		getline(stream, dataelement.Audiotype, ',');
		getline(stream, dataelement.FileName, ',');
		getline(stream, dataelement.Resourcetype, ',');
		getline(stream, looptype, ',');
		getline(stream, streamtype, ',');
		getline(stream, maxvolume, ',');

		// フラグ設定
		dataelement.Loop = stof(looptype) != 0;
		dataelement.StreamType = stof(streamtype);
		dataelement.MaxVolume = stof(maxvolume);
		
		audiotype = dataelement.Audiotype;
		name = dataelement.FileName;
		resourcetype = dataelement.Resourcetype;

		// ファイルのロード
		if (resourcetype == "wav")
		{
			dataelement.Loadsoundfile = new CLoadWave((m_cAudioPath + audiotype + "/" + name + ".wav"), dataelement.Loop);
		}
		else if (resourcetype == "ogg") {
			// 現在使用不可
			//dataelement.Loadsoundfile = new CLoadOgg((m_cAudioPath + audiotype + "/" + name + ".ogg"), dataelement.Loop);
		}
		else
		{
			printf("filetypeが規定範囲外です");
		}

		// Waveformatの取得
		dataelement.Waveformat = dataelement.Loadsoundfile->GetWaveFormat();

		// Waveformatの設定
		m_Formatlist.push_back(dataelement);
	}

}

//====================================================
//  @fn
//	登録されたリソースを取得する関数
//	@param Listnumb 欲しいサウンドデータ(Csvの順番参照)番号
//	@return SoundElement 必要な情報を返す
//	
SoundElement CWaveformatData::GetWaveElement(int listnumb)
{
	return m_Formatlist[listnumb];
}

//====================================================
//  @fn
//	登録されたリソースを取得する関数
//	@param Listnumb 欲しいサウンドデータ(Csvの名称参照)の名前
//	@return SoundElement 必要な情報を返す
//	
SoundElement CWaveformatData::GetWaveElement(std::string soundame)
{
	SoundElement _null;
	
	if (m_Formatlist.empty())
	{
		return _null;
	}

	for each (auto var in m_Formatlist)
	{
		if (var.FileName != soundame)
			continue;

		return var;
	}

	return _null;

}