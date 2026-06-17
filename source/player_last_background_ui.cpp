#include<sstream>
#include<fstream>
#include<string>
#include<memory>
#include<functional>
#include"player_last_background_ui.h"
#include"object_base.h"
#include"image_data.h"
#include"object_2D.h"
#include"draw_2D.h"
#include"csv_file_assistant.h"

PlayerLastBackGroundUI::PlayerLastBackGroundUI()
{
	LoadFile();
}

PlayerLastBackGroundUI::~PlayerLastBackGroundUI()
{

}

void PlayerLastBackGroundUI::Draw()
{
	Draw2D::Blend([this]() -> void {last_background_->Draw(); }, alpha_value_);
}

void PlayerLastBackGroundUI::LoadFile()
{
	std::ifstream file("data/csv/ui/player/last_background_data.csv");
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
	}

	// 最初の行を飛ばす
	std::getline(file, line);
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		ImageData image_data = {};
		image_data.path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		image_data.width = CSVFileAssistant::GetIntOfCSVFile(ss, data);
		image_data.height = CSVFileAssistant::GetIntOfCSVFile(ss, data);

		VECTOR pos = CSVFileAssistant::GetVector2DOfCSVFile(ss, data);
		float size_rate = CSVFileAssistant::GetFloatOfCSVFile(ss, data); 
		float rot_z = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		alpha_value_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		last_background_ = std::make_shared<Object2D>(image_data, pos, size_rate, rot_z);
	}

}



