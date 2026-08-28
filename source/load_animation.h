#pragma once
#include"animation_data.h"
#include"animation_2d_data.h"

inline void LoadAnimation(AnimationData& data, const char name[], int ind, float play_speed, int priority, float cancel_time,bool loop,std::string next_anim_name)
{
	data.handle = MV1LoadModel(name);
	if (data.handle == -1) { printfDx("データ読み込み失敗\n"); }

	data.anim_index = ind;
	data.attach_index = 0;

	data.priority	= priority;

	data.play_time  = 0.f;
	data.total_time = 0.f;
	data.play_speed = play_speed;
	data.cancel_time = cancel_time;
	data.loop = loop;
	data.next_anim_name = next_anim_name;
}

/// <summary>
/// 
/// </summary>
/// <param name="data">アニメーション</param>
/// <param name="string_datas">文字データの集合体</param>
/// <param name="row_num">何行目なのか</param>
inline void LoadAnimationToStringDatas(AnimationData& data, const std::vector<std::string> string_datas,const int init_index)
{
	//今の行の一列目の要素は名前なのでとばす
	int index = init_index + 1;
	data.handle = MV1LoadModel(string_datas[index].c_str());
	index++;
	if (data.handle == -1) 
	{ 
		//printfDx("データ読み込み失敗\n");
	}

	data.anim_index = stoi(string_datas[index]);
	index++;
	data.attach_index = 0;

	data.play_speed = stof(string_datas[index]);
	index++;

	data.priority = stoi(string_datas[index]);
	index++;
	data.play_time = 0.f;
	data.total_time = 0.f;

	data.loop = stoi(string_datas[index]);
	index++;
	data.cancel_time = stof(string_datas[index]);
	index++;
	data.next_anim_name = string_datas[index];
}

inline void LoadAnimation2D(Animation2DData& data, const std::string& file_path,
	unsigned int side_index, unsigned int vertical_index,int image_width,int image_height, int priority,
	float total_time,bool loop,const std::string& next_anim_name)
{
	int max_index = vertical_index * side_index;
	data.handles.resize(max_index);
	int value = LoadDivGraph(file_path.c_str(), max_index, side_index, vertical_index,
		static_cast<int>(float(image_width) / side_index), static_cast<int>(float(image_height) / vertical_index), data.handles.data());
	if (value == -1) { printfDx("失敗\n"); }
	data.current_anim_index = 0;
	data.max_anim_index = max_index;
	data.total_time = total_time;
	data.play_time = 0.f;
	data.cool_time = data.total_time / max_index;
	data.loop = loop;
	data.next_anim_name = next_anim_name;
}
