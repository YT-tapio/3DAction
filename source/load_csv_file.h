#pragma once
#include"file_data.h"

class LoadCSVFile
{
public:

	~LoadCSVFile() = default;

	static LoadCSVFile& GetInstance()
	{
		static LoadCSVFile instance;
		return instance;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="file_path">ファイルの場所</param>
	/// <param name="pass_row">何行とばすか</param>
	/// <param name="name">指定のものをとる場合</param>
	/// <returns></returns>
	FileData GetData(const std::string& file_path, const int pass_row,std::string name = "empty");

private:

	LoadCSVFile();

	bool CheckSameData(FileData& file_data);

private:

	std::vector<FileData> file_datas_;

};