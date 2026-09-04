#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"animator_2d.h"
#include"animation_2d_data.h"
#include"csv_file_assistant.h"
#include"load_animation.h"
#include"FPS.h"

Animator2D::Animator2D(const std::string& data_file_path)
	: now_anim_name_("test")
{
	LoadFile(data_file_path);
}

Animator2D::~Animator2D()
{
	// アニメーションのデータ開放
	for (auto& data : datas_)
	{
		for (auto& handle : data.second.handles)
		{
			if (handle != -1)
			{
				DeleteGraph(handle);
				handle = -1;
			}
		}
	}
	datas_.clear();
	request_names_.clear();

}


void Animator2D::Init()
{

}

void Animator2D::Update()
{
	// アニメーションの変更
	// とりあえず再生

	auto& data = datas_[now_anim_name_];
	data.play_time += FPS::GetInstance().GetDeltaTime();

	if (data.play_time > data.cool_time * (data.current_anim_index + 1))
	{
		data.current_anim_index++;
		if (data.play_time >= data.total_time)
		{
			if (data.loop)
			{
				data.play_time -= data.total_time;
				data.current_anim_index = 0;
			}
			else
			{
				data.current_anim_index = data.max_anim_index - 1;
			}
		}
	}
}

void Animator2D::PlayRequest(std::string name)
{

}

void Animator2D::Start()
{

}

void Animator2D::Stop()
{

}

void Animator2D::Cancel()
{

}

const std::string Animator2D::GetNowAnimName() const
{
	return now_anim_name_;
}

const int Animator2D::GetNowHandle() const
{
	auto data = datas_.find(now_anim_name_);
	if (data == datas_.end()) { return -1; }
	return data->second.handles[data->second.current_anim_index];
}

const int Animator2D::GetHandle(const std::string& name) const
{
	auto data = datas_.find(name);
	if (data == datas_.end()) { return -1; }
	return data->second.handles[data->second.current_anim_index];
}

void Animator2D::LoadFile(const std::string& data_file_path)
{
	// データ
	std::ifstream file(data_file_path);
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
		Animation2DData anim_data = {};
		auto my_name = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		auto file_path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		auto side_index = CSVFileAssistant::GetIntOfCSVFile(ss, data);
		auto vertical_index = CSVFileAssistant::GetIntOfCSVFile(ss, data);
		auto width = CSVFileAssistant::GetIntOfCSVFile(ss, data);
		auto height = CSVFileAssistant::GetIntOfCSVFile(ss, data);
		auto priority = CSVFileAssistant::GetIntOfCSVFile(ss, data);
		auto total_time = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		auto loop = CSVFileAssistant::GetBoolOfCSVFile(ss, data);
		auto next_anim_name= CSVFileAssistant::GetStringOfCSVFile(ss, data);
		LoadAnimation2D(anim_data, file_path, side_index, vertical_index, width, height, priority, total_time, loop, next_anim_name);
		datas_[my_name] = anim_data;
	}

}
