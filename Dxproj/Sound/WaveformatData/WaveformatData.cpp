#include "WaveformatData.h"

//====================================================
//	@fn
//	�w��Csv�̓ǂݍ���
//	@param filepath csv�t�@�C���̖��O	
//
CWaveformatData::CWaveformatData(std::string filepath)
{
	RegistWaveformat(filepath);
}

//====================================================
//	@fn
//	�o�^���ꂽWAVEFORMATEX���̍폜
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
//	�O�����\�[�X��WAVEFORMATEX�ɓo�^���邽�߂̏���
//	@param filepath csv�̃t�@�C�������L������
//
void CWaveformatData::RegistWaveformat(std::string filepath)
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

		// �t���O�ݒ�
		dataelement.Loop = stof(looptype) != 0;
		dataelement.StreamType = stof(streamtype);
		dataelement.MaxVolume = stof(maxvolume);
		
		audiotype = dataelement.Audiotype;
		name = dataelement.FileName;
		resourcetype = dataelement.Resourcetype;

		// �t�@�C���̃��[�h
		if (resourcetype == "wav")
		{
			dataelement.Loadsoundfile = new CLoadWave((m_cAudioPath + audiotype + "/" + name + ".wav"), dataelement.Loop);
		}
		else if (resourcetype == "ogg") {
			// ���ݎg�p�s��
			//dataelement.Loadsoundfile = new CLoadOgg((m_cAudioPath + audiotype + "/" + name + ".ogg"), dataelement.Loop);
		}
		else
		{
			printf("filetype���K��͈͊O�ł�");
		}

		// Waveformat�̎擾
		dataelement.Waveformat = dataelement.Loadsoundfile->GetWaveFormat();

		// Waveformat�̐ݒ�
		m_Formatlist.push_back(dataelement);
	}

}

//====================================================
//  @fn
//	�o�^���ꂽ���\�[�X���擾����֐�
//	@param Listnumb �~�����T�E���h�f�[�^(Csv�̏��ԎQ��)�ԍ�
//	@return SoundElement �K�v�ȏ���Ԃ�
//	
SoundElement CWaveformatData::GetWaveElement(int listnumb)
{
	return m_Formatlist[listnumb];
}

//====================================================
//  @fn
//	�o�^���ꂽ���\�[�X���擾����֐�
//	@param Listnumb �~�����T�E���h�f�[�^(Csv�̖��̎Q��)�̖��O
//	@return SoundElement �K�v�ȏ���Ԃ�
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