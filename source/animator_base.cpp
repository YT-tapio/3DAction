#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"animator_base.h"
#include"animation_data.h"
#include"load_animation.h"

AnimatorBase::AnimatorBase(const char* data_file_path,int handle)
{
	kDataFilePath = data_file_path;
	now_anim_name_ = "nothing";
	handle_ = handle;
	is_end_ = FALSE;
}

AnimatorBase::~AnimatorBase()
{
	// animationを消去
	for (auto& animation : animation_datas_)
	{
		MV1DeleteModel(animation.second.handle);
	}
}

void AnimatorBase::Init()
{
	LoadFile(kDataFilePath);
}

void AnimatorBase::Update()
{

}

void AnimatorBase::PlayRequest(std::string name)
{
	request_names_.push_back(name);
}

void AnimatorBase::LoadFile(const char* file_path)
{
	std::ifstream file(file_path);
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
	}

	// 最初の行を飛ばす
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;	// csvからの文字列をもらう
		std::string anim_name;
		std::string anim_file_path;
		int anim_index		= -1;
		int priority		= -1;
		int loop = -1;
		float play_speed	= 0.f;
		AnimationData anim_data = {};

		// アニメーションの名前
		std::getline(ss, data, ',');
		anim_name = data;

		// アニメーションファイルの名前
		std::getline(ss, data, ',');
		anim_file_path = data;

		// アニメーションの識別番号
		std::getline(ss, data, ',');
		anim_index = std::stoi(data);

		// アニメーションの再生速度
		std::getline(ss, data, ',');
		play_speed = std::stof(data);
	
		// アニメーションの優先度
		std::getline(ss, data, ',');
		priority = std::stoi(data);

		// ループするかどうか
		std::getline(ss, data, ',');
		loop = (std::stoi(data) == 1);

		// アニメーションデータを生成
		LoadAnimation(anim_data, anim_file_path.c_str(), anim_index, play_speed, priority, loop);
		animation_datas_[anim_name] = anim_data;
	}
}

void AnimatorBase::ResetRequest()
{
	request_names_.clear();
}

const float AnimatorBase::GetPlayTime(std::string name) const
{
	float play_time = -1.f;

	for (const auto& animation : animation_datas_)
	{
		if (name != animation.first) { continue; }
		play_time = animation.second.play_time;
	}

	return play_time;
}

const std::string AnimatorBase::GetNowAniName() const
{
	return now_anim_name_;
}

