#include<functional>
#include<string>
#include<fstream>
#include<sstream>
#include"DxLib.h"
#include"hp_actual_value_ui.h"
#include"csv_file_assistant.h"
#include"font.h"
#include"color.h"


HPActualValueUI::HPActualValueUI(const std::string& file_path,std::function<int()> get_current_hp)
	: get_current_hp_(get_current_hp)
{
	LoadFile(file_path,get_current_hp);
}

HPActualValueUI::~HPActualValueUI()
{
	DeleteFontToHandle(font_handle_);
}

void HPActualValueUI::Init()
{

}

const void HPActualValueUI::Draw() const
{
	DrawFormatStringToHandle(static_cast<int>(pos_.x), static_cast<int>(pos_.y), Color::kRed, font_handle_, "%d", get_current_hp_());
}

void HPActualValueUI::LoadFile(const std::string& file_path,std::function<int()> get_current_hp)
{
	std::ifstream file(file_path);
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
	}

	// 最初の行を飛ばす
	std::getline(file, line);
	std::getline(file, line);
	std::string font_data_path = "";
	VECTOR pos = VectorAssistant::VGetZero();
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		font_data_path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		pos = CSVFileAssistant::GetVector2DOfCSVFile(ss,data);
	}
	font_handle_ = Font::CreateHandleOfFile(font_data_path);
	pos_ = pos;
}