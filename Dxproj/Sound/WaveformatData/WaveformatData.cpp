#include "WaveformatData.h"

//====================================================
//	@fn
//	指定Csvの読み込み
//	@param filepath csvファイルの名前	
//
CWaveformatData::CWaveformatData(std::string filepath, std::string Soundname)
{
	RegistWaveformat(filepath,Soundname);
}

//====================================================
//	@fn
//	登録されたWAVEFORMATEX情報の削除
//
CWaveformatData::~CWaveformatData()
{
	delete m_Format.Loadsoundfile;
}

//====================================================
//  @fn
//	外部リソースをWAVEFORMATEXに登録するための処理
//	@param filepath csvのファイル名を記入する
//
void CWaveformatData::RegistWaveformat(std::string filepath, std::string Soundname)
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

		if (dataelement.FileName != Soundname)
			continue;

		// フラグ設定
		dataelement.Loop = stof(looptype) != 0;
		dataelement.StreamType = stoi(streamtype);
		dataelement.MaxVolume = stof(maxvolume);
		
		audiotype = dataelement.Audiotype;
		name = dataelement.FileName;
		resourcetype = dataelement.Resourcetype;

		dataelement.Loadsoundfile = nullptr;
		dataelement.Waveformat = nullptr;

		// ファイルのロード
		if (dataelement.Resourcetype == "wav")
		{
			dataelement.Loadsoundfile = new CLoadWave((m_cAudioPath + dataelement.Audiotype + "/" + dataelement.FileName + ".wav"), dataelement.Loop);
		}
		else if (dataelement.Resourcetype == "ogg") {
			// 現在使用不可
			dataelement.Loadsoundfile = new CLoadOgg((m_cAudioPath + audiotype + "/" + name + ".ogg"), dataelement.Loop);
		}
		else
		{
			printf("filetypeが規定範囲外です");
		}

		// Waveformatの取得
		dataelement.Waveformat = dataelement.Loadsoundfile->GetWaveFormat();

		m_Format = dataelement;		
	}

}

SoundElement CWaveformatData::GetWaveElement()
{
	return m_Format;
}