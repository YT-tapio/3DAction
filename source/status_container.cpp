#include<fstream>
#include<sstream>
#include<string>
#include"status.h"
#include"status_container.h"
#include"csv_file_assistant.h"

StatusContainer::StatusContainer(const std::string owner_name)
{
	LoadFile(owner_name);
	Init();
}

StatusContainer::~StatusContainer()
{

}

void StatusContainer::Init()
{
	current_status_ = base_status_;
}

void StatusContainer::Update()
{
	//バフされる量をあらかじめ決めておく
}

void StatusContainer::Debug()
{
	
}

const Status StatusContainer::GetCurrentStatus() const
{
	return current_status_;
}

void StatusContainer::LoadFile(const std::string owner_name)
{
	// データ読み取り
	
	const std::string file_path = "data/csv/status/status_data.csv";

	std::ifstream file(file_path);
	std::string line;

	if (!file)
	{
		printfDx("csvファイル(status) 読み込み失敗\n");
	}

	// 最初の行は飛ばす
	std::getline(file, line);

	// 検索外の場合のフラグ
	bool is_empty = TRUE;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		if (owner_name == CSVFileAssistant::GetStringOfCSVFile(ss, data)) { continue; }

		// データを用意
		Status base_data = {};
		
		base_data.hp			= CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		base_data.physical_atk	= CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		base_data.physical_def	= CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		base_data.magic_atk		= CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		base_data.magic_def		= CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		base_data.stamina		= CSVFileAssistant::GetFloatOfCSVFile(ss, data);

		base_status_ = base_data;
		is_empty = FALSE;

		break;
	}

	if (is_empty)
	{
		printfDx("そのようなゲーム内キャラクターはいません\n");
	}
}

