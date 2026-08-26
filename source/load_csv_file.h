#pragma once

class LoadCSVFile
{
public:

	~LoadCSVFile() = default;

	static LoadCSVFile& Getnstnce()
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
	std::vector<std::string> GetDatas(const std::string& file_path, const int pass_row,std::string name = "empty");

private:

	LoadCSVFile();

private:

	std::unordered_map<std::string,std::vector<std::string>> string_datas_;

};