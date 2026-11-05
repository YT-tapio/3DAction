#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"font_data.h"
#include"font.h"
#include"load_csv_file.h"

void FontData::Awake()
{
	const std::string kFilePath = "data/csv/font/font_datas.csv";
	const int kPassRow = 1;
	// フォントをロード
	auto file_data = LoadCSVFile::GetInstance().GetData(kFilePath,kPassRow);

	for (int i = 0; i < file_data.indices.size(); i++)
	{
		// 一列目の番号
		int first_vertical_num = i * 2;
		// フォント名を受け取る
		auto name = file_data.string_datas[first_vertical_num];
		auto file_path = file_data.string_datas[first_vertical_num + 1];
		auto font = Font::CreateHandleOfFile(file_path);

		if (font == -1)
		{
			printfDx("fontを読み込み失敗:%s\n",name.c_str());
			continue;
		}

		font_handles_[name] = font;
	}

}

void FontData::DeleteHandle()
{
	for (auto& font_data : font_handles_)
	{
		DeleteFontToHandle(font_data.second);
		font_data.second = -1;
	}

	font_handles_.clear();
}

const int FontData::GetHandle(const std::string name) const
{
	auto font_data = font_handles_.find(name);
	if (font_data != font_handles_.end())
	{
		return font_data->second;
	}
	printfDx("その名前のフォントは存在しません：%s\n", name.c_str());
	return -1;
}

FontData::FontData()
{

}
