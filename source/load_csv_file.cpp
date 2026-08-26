#include<vector>
#include<string>
#include<unordered_map>
#include<fstream>
#include<sstream>
#include"DxLib.h"
#include"load_csv_file.h"
#include"csv_file_assistant.h"

std::vector<std::string> LoadCSVFile::GetDatas(const std::string& file_path,const int pass_row,std::string name)
{
	std::vector<std::string> datas;

	std::ifstream file(file_path);
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
		return datas;
	}

	// 最初の数行を都バス
	for (int i = 0; i <= pass_row; i++)
	{
		std::getline(file, line);
	}
	

	while (std::getline(file, line))
	{
		
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		// 指定がある場合
		if (name != "empty")
		{
			// その指定と一致していないのならもう一度
			if (name != CSVFileAssistant::GetStringOfCSVFile(ss, data))
			{
				continue;
			}
		}

		while (std::getline(ss, data,','))
		{
			// 要素が空になったら抜け出す
			if (data.empty()) { break; }
			
			

		}
		// 一行だけのデータを受け取る
		break;
	}

	// データの保持

	return datas;
}


LoadCSVFile::LoadCSVFile()
{

}