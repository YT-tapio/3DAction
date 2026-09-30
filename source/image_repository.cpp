#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"image_repository.h"
#include"load_csv_file.h"

void ImageRepository::Load()
{

	auto datas = LoadCSVFile::GetInstance().GetData("data/csv/image_data.csv",1);

	// s”•ªŒJ‚è•Ô‚·
	for (int i = 0; i < datas.indices.size(); i++)
	{
		int first_num = i * 2;
		std::string name = datas.string_datas[first_num];
		std::string file_path = datas.string_datas[first_num + 1];

		images_[name] = LoadGraph(file_path.c_str());
		if (images_[name] == -1)
		{
			printfDx("‰æ‘œ“Ç‚İ‚İ¸”sF%s\n", name);
		}
	}
}

const int ImageRepository::GetHandle(const std::string& name) const
{
	auto image = images_.find(name);
	if (image == images_.end()) 
	{
		printfDx("‚»‚Ì‰æ‘œ‚Í‘¶İ‚µ‚Ü‚¹‚ñF%s\n", name);
		return -1;
	}
	return image->second;
}

ImageRepository::ImageRepository()
{

}