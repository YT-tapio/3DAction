#pragma once
#include<string>
#include<vector>
#include"file_name_data.h"

struct FileData
{
	FileNameData name_data;
	std::vector<std::string> string_datas;

	// 1s’PˆÊ‚Ì—v‘f”
	std::vector<int> indices;
};