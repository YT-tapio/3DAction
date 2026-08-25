#include<string>
#include"DxLib.h"
#include"sound_2D.h"
#include<fstream>
#include<sstream>
#include"csv_file_assistant.h"

Sound2D::Sound2D(const std::string& file_path)
{
	LoadFile(file_path);
}

Sound2D::~Sound2D()
{

}

void Sound2D::Init()
{

}

void Sound2D::LoadFile(const std::string& file_path)
{
	std::ifstream file(file_path);
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
	}

	// 最初の行を飛ばす
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		std::string data_file_path;

		name_ = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		data_file_path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		handle_ = LoadSoundMem(data_file_path.c_str());
		volume_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		loop_ = CSVFileAssistant::GetBoolOfCSVFile(ss, data);
		if (handle_ == -1)
		{
			printfDx("サウンド読み込みしっぱい\n");
		}
		else
		{
			ChangeVolumeSoundMem(volume_, handle_);
		}
		
	}

	
}

