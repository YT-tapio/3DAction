#include<vector>
#include<string>
#include<unordered_map>
#include<fstream>
#include<sstream>
#include"DxLib.h"
#include"load_csv_file.h"
#include"csv_file_assistant.h"

FileData LoadCSVFile::GetData(const std::string& file_path,const int pass_row,std::string target_name)
{
	FileData file_data;
	file_data.name_data.file_path = file_path;
	file_data.name_data.target_name = target_name;
	if (CheckSameData(file_data))
	{
		//printfDx("Same File\n");
		return file_data;
	}
	std::ifstream file(file_path);
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
		return file_data;
	}

	// 最初の数行をとばす
	for (int i = 0; i < pass_row; i++)
	{
		std::getline(file, line);
	}
	
	while (std::getline(file, line))
	{
		int index = 0;
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		// 指定がある場合
		if (target_name != "empty")
		{
			// その指定と一致していないのならもう一度
			if (target_name != CSVFileAssistant::GetStringOfCSVFile(ss, data))
			{
				continue;
			}
		}

		while (std::getline(ss, data,','))
		{
			file_data.string_datas.push_back(data);
			// 要素数をカウント
			index++;
		}
		file_data.indices.push_back(index);
	}
	
	// データの保持
	file_datas_.push_back(file_data);

	return file_data;
}

LoadCSVFile::LoadCSVFile()
{

}

bool LoadCSVFile::CheckSameData(FileData& current_file_data)
{
	for (const auto file_data : file_datas_)
	{
		const auto current_name_data = current_file_data.name_data;
		const auto name_data = file_data.name_data;
		// ファイルの名前が一致
		if (current_name_data.file_path == name_data.file_path)
		{
			// ターゲットが一致
			if (current_name_data.target_name == name_data.target_name)
			{
				// 要素のコピーをする
				current_file_data.string_datas = file_data.string_datas;
				current_file_data.indices = file_data.indices;
			}
			return TRUE;
		}
	}
	return FALSE;
}