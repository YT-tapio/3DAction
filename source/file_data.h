#pragma once
#include<string>
#include<vector>
#include"file_name_data.h"

struct FileData
{
	FileNameData name_data;					// ファイルの名前
	std::vector<std::string> string_datas;	// 文字
	std::vector<int> indices;				// 1行単位の要素数
};