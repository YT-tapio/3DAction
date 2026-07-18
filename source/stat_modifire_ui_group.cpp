#include<unordered_map>
#include<string>
#include"DxLib.h"
#include"stat_modifire_ui_group.h"
#include"draw_2D.h"
#include<fstream>
#include<sstream>
#include"csv_file_assistant.h"

StatModifireUIGroup::StatModifireUIGroup(const std::string& file_path)
{
	LoadFile(file_path);
	Init();
}

StatModifireUIGroup::~StatModifireUIGroup()
{

}

void StatModifireUIGroup::Init()
{
	// 空のデータ
	ActiveStatModifireUI empty;
	for (int i = 0; i < kMaxStatModifireUINum; i++)
	{
		active_stat_modifire_uis_[i] = empty;
	}

	// 一つ余分に作る
	active_stat_modifire_uis_[kMaxStatModifireUINum] = empty;
}

void StatModifireUIGroup::Update()
{
	int i = 0;

	while (TRUE)
	{
		if (active_stat_modifire_uis_[i].end_condition != nullptr)
		{
			// 終了したら
			if (active_stat_modifire_uis_[i].end_condition())
			{
				// 要素を交換しカウントもしない
				ChangeActiveStatModifireUI(i);
			}
			else
			{
				i++;
			}
		}
		else
		{
			break;
		}
	}


}

void StatModifireUIGroup::Draw()
{
	for (int i = 0; i < kMaxStatModifireUINum; i++)
	{
		auto handle = active_stat_modifire_uis_[i].handle;
		// 描画するposを定める
		auto pos = base_pos_;
		
		// 要素がある場合
		if (handle  > 0)
		{
			Draw2D::RotaGraph(pos, size_rate_, rot_z_, handle, TRUE);
		}
		else if(handle == -2)
		{
			Draw2D::Box(pos, 10, 10, GetColor(0, 0, 0), TRUE);
		}
		else
		{
			break;
		}
	}
}

void StatModifireUIGroup::Spawn(std::function<bool()> end_condition,StatType stat_type,ModifireOperation operation)
{
	for (int i = 0; i < kMaxStatModifireUINum; i++)
	{
		// nullptrの時
		if (active_stat_modifire_uis_[i].end_condition == nullptr)
		{
			active_stat_modifire_uis_[i].end_condition = end_condition;
			active_stat_modifire_uis_[i].handle = -2;
			break;
		}
	}
}

void StatModifireUIGroup::LoadFile(const std::string& file_path)
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

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		base_pos_ = CSVFileAssistant::GetVector2DOfCSVFile(ss, data);
		size_rate_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		rot_z_ = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
	}

}

void StatModifireUIGroup::ChangeActiveStatModifireUI(int index)
{

	for (int i = index; i < kMaxStatModifireUINum; i++)
	{
		// 終了条件がない場合
		if (active_stat_modifire_uis_[i].end_condition == nullptr)
		{
			break;
		}
		active_stat_modifire_uis_[i] = active_stat_modifire_uis_[i + 1];
	}

}