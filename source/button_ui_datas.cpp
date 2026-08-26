#include<unordered_map>
#include<string>
#include<sstream>
#include<fstream>
#include"DxLib.h"
#include"button_ui_datas.h"
#include"csv_file_assistant.h"

void ButtonUIDatas::Awake()
{
	LoadFile();
}

const int ButtonUIDatas::GetHandle(const std::string& name) const
{
	auto data = button_ui_handles_.find(name);
	if (data == button_ui_handles_.end()) { return -1; }
	return data->second;
}

ButtonUIDatas::ButtonUIDatas()
{

}

void ButtonUIDatas::LoadFile()
{
	// ボタンのデータを取得

	std::ifstream file("data/csv/ui/button/button_datas.csv");
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
		return;
	}

	// 最初の行を飛ばす
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;
		auto name = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		auto file_path = CSVFileAssistant::GetStringOfCSVFile(ss, data);

		auto handle = LoadGraph(file_path.c_str());
		if (handle == -1)
		{
			printfDx("読み込み失敗\n");
		}
		button_ui_handles_[name] = handle;
	}
	


}