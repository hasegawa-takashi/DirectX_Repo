#include "WaveformatData.h"

//====================================================
//	@fn
//	�w��Csv�̓ǂݍ���
//	@param filepath csv�t�@�C���̖��O	
//
CWaveformatData::CWaveformatData(std::string filepath, std::string Soundname)
{
	RegistWaveformat(filepath,Soundname);
}

//====================================================
//	@fn
//	�o�^���ꂽWAVEFORMATEX���̍폜
//
CWaveformatData::~CWaveformatData()
{
	delete m_Format.Loadsoundfile;
}

//====================================================
//  @fn
//	�O�����\�[�X��WAVEFORMATEX�ɓo�^���邽�߂̏���
//	@param filepath csv�̃t�@�C�������L������
//
void CWaveformatData::RegistWaveformat(std::string filepath, std::string Soundname)
{

	// CSV�t�@�C���̓ǂݍ���
	std::ifstream ifs( m_cAudioPath + filepath + ".csv");
	
	if (!ifs)
	{
		printf(".csv�t�@�C���̓ǂݍ��݂Ɏ��s���܂���");
		return;
	}

	// CSV�̓ǂݍ���
	std::string str;

	getline(ifs, str);//�s�v�����̓ǂݍ���
	
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

		// �t���O�ݒ�
		dataelement.Loop = stof(looptype) != 0;
		dataelement.StreamType = stoi(streamtype);
		dataelement.MaxVolume = stof(maxvolume);
		
		audiotype = dataelement.Audiotype;
		name = dataelement.FileName;
		resourcetype = dataelement.Resourcetype;

		dataelement.Loadsoundfile = nullptr;
		dataelement.Waveformat = nullptr;

		// �t�@�C���̃��[�h
		if (dataelement.Resourcetype == "wav")
		{
			dataelement.Loadsoundfile = new CLoadWave((m_cAudioPath + dataelement.Audiotype + "/" + dataelement.FileName + ".wav"), dataelement.Loop);
		}
		else if (dataelement.Resourcetype == "ogg") {
			// ���ݎg�p�s��
			dataelement.Loadsoundfile = new CLoadOgg((m_cAudioPath + audiotype + "/" + name + ".ogg"), dataelement.Loop);
		}
		else
		{
			printf("filetype���K��͈͊O�ł�");
		}

		// Waveformat�̎擾
		dataelement.Waveformat = dataelement.Loadsoundfile->GetWaveFormat();

		m_Format = dataelement;		
	}

}

SoundElement CWaveformatData::GetWaveElement()
{
	return m_Format;
}