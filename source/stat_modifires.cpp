#include<fstream>
#include<sstream>
#include<unordered_map>
#include<string>
#include"stat_modifire.h"
#include"stat_modifires.h"
#include"csv_file_assistant.h"

StatModifires::StatModifires()
{
	Awake();
}

StatModifires::~StatModifires()
{
	End();
}

void StatModifires::Awake()
{
	// ファイルの読み込み
	LoadFile();
}

void StatModifires::End()
{
	effecacy_datas_.clear();
}

const StatModifire StatModifires::GetData(const std::string& name) const
{
	auto data = effecacy_datas_.find(name);
	if(data == effecacy_datas_.end())
	{
		printfDx("そんなバフはないです\n");
		return empty_data_;
	}
	return data->second;
}

void StatModifires::LoadFile()
{
	// csvfileからデータの受け取り
	std::ifstream file(kFilePath.c_str());
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
		std::string string_data;
		StatModifire data = {};

		auto name	 = CSVFileAssistant::GetStringOfCSVFile(ss, string_data);	// 名前
		data.rate = CSVFileAssistant::GetFloatOfCSVFile(ss, string_data);	// バフの量
		data.time = CSVFileAssistant::GetFloatOfCSVFile(ss, string_data);	// 時間
		data.operation = static_cast<ModifireOperation>(CSVFileAssistant::GetIntOfCSVFile(ss, string_data));	//  バフかデバフか
		data.type = static_cast<StatType>(CSVFileAssistant::GetIntOfCSVFile(ss, string_data));	// カテゴリ

		effecacy_datas_[name] = data;
	}

}
