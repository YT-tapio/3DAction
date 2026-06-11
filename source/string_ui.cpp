#include<string>
#include<fstream>
#include<sstream>
#include"DxLib.h"
#include"string_ui.h"
#include<windows.h>
#include"csv_file_assistant.h"
#include"font.h"

StringUI::StringUI(const std::string& data_file_path)
	: font_handle_(-1)
{
	LoadFile(data_file_path);
}

StringUI::~StringUI()
{
	DeleteFontToHandle(font_handle_);
}

void StringUI::Init()
{

}

void StringUI::Update()
{

}

const void StringUI::Draw() const
{
	
}

void StringUI::LoadFile(const std::string& data_file_path)
{
	std::ifstream file(data_file_path);
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

		font_data_path	= CSVFileAssistant::GetStringOfCSVFile(ss, data);
		pos				= CSVFileAssistant::GetVector2DOfCSVFile(ss, data);
	}
	font_handle_ = Font::CreateHandleOfFile(font_data_path);
	pos_ = pos;
}