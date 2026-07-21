#include<unordered_map>
#include<fstream>
#include<sstream>
#include<string>
#include"DxLib.h"
#include"stat_modifire_ui_data.h"
#include<functional>
#include"csv_file_assistant.h"

void StatModifireUIData::Load()
{
	// データ
	std::ifstream file("data/csv/ui/stat_modifire/stat_modifire_image_data.csv");
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
		std::string data;

		// どんなバフか

		std::string stat_modifire_name = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		std::string file_path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		int handle = LoadGraph(file_path.c_str());
		if (handle == -1)
		{
			printfDx("画像読み込み失敗\n");
		}
		handles_[stat_modifire_name] = handle;
	}

}

void StatModifireUIData::End()
{
	
}

const int StatModifireUIData::GetHandle(StatType type, ModifireOperation operation) const
{
	std::string name;

	switch (type)
	{
	case StatType::kPhysicalATK:
		name = "physical_atk_";
		break;
	case StatType::kPhysicalDEF:
		name = "physical_def_";
		break;

	case StatType::kMagicATK:
		name = "magic_atk_";
		break;
	case StatType::kMagicDEF:
		name = "magic_def_";
		break;
	default:
		printfDx("そのような効果はないです\n");
		return -2;
		break;
	}

	switch (operation)
	{
	case ModifireOperation::kBuff:
		name = name + "buff";
		break;
	case ModifireOperation::kDeBuff:
		name = name + "debuff";
		break;

	case ModifireOperation::kEmpty:
	default:
		printfDx("そのような効果はないです\n");
		return -2;
		break;
	}

	auto handle = handles_.find(name);

	if (handle == handles_.end())
	{
		printfDx("その効果は登録されていません\n");
		return -2;
	}

	return handle->second;
}

StatModifireUIData::StatModifireUIData()
{

}