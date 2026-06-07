#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"animator_base.h"
#include"animation_data.h"
#include"load_animation.h"
#include"csv_file_assistant.h"
#include"FPS.h"

AnimatorBase::AnimatorBase(const std::string data_file_path, int handle)
{
	kDataFilePath		= "data/csv/animation/" + data_file_path +"_animation.csv";
	now_anim_name_		= "nothing";
	before_anim_name_	= "nothing";
	next_anim_name_ = "nothing";
	handle_				= handle;
	is_end_				= FALSE;
	is_blending_		= FALSE;
	is_stop_			= FALSE;
	can_cancel_		= FALSE;
	blend_rate_ = 0.f;
}

AnimatorBase::~AnimatorBase()
{
	// animationを消去
	for (auto& animation : animation_datas_)
	{
		MV1DeleteModel(animation.second.handle);
	}
	animation_datas_.clear();
}

void AnimatorBase::Init()
{
	LoadFile(kDataFilePath);
	blend_rate_ = 0.f;
}

void AnimatorBase::Update()
{
	// もし次に続くアニメーションがあるなら
	if (CheckNextAnimation())
	{
		PlayRequest(animation_datas_[now_anim_name_].next_anim_name);
	}

	// リクエストの整理をする
	ChangeAnimation();
	
	// アニメーションをチェンジ
	if (ChangeCondition())
	{
		// ブレンド中は前回のをデタッチにする
		if (is_blending_)
		{
			auto& before_anim_data = animation_datas_[before_anim_name_];
			MV1DetachAnim(handle_, before_anim_data.attach_index);
			before_anim_data.attach_index = -1;
			before_anim_data.play_time = 0.f;
		}

		before_anim_name_ = now_anim_name_;
		now_anim_name_ = next_anim_name_;
		
		auto& now_anim_data = animation_datas_[now_anim_name_];

		// キャンセルを無効にする
		can_cancel_ = FALSE;
		is_end_ = FALSE;
		is_blending_ = TRUE;	// 何もないとブレンドしない
		blend_rate_ = 0.f;

		if (before_anim_name_ == kNothing)
		{
			is_blending_ = FALSE;
		}

		// アタッチ
		now_anim_data.attach_index = MV1AttachAnim(handle_, now_anim_data.anim_index,
			now_anim_data.handle, FALSE);

		// トータルタイムを取得
		now_anim_data.total_time = MV1GetAttachAnimTotalTime(handle_, now_anim_data.attach_index);
		// キャンセルを定める
		if (now_anim_data.cancel_time == -1)
		{
			now_anim_data.cancel_time = now_anim_data.total_time;
		}

		now_anim_data.play_time = 0.f;

		if (now_anim_data.attach_index == -1) { printfDx("アタッチに失敗しました\n"); }
		if (now_anim_data.total_time < 0.f) { printfDx("トータルおかしい\n"); }
	}
	auto& now_anim_data = animation_datas_[now_anim_name_];

	//ここで
	if (is_blending_) { 	PlayTimeUpdate(animation_datas_[before_anim_name_]); }

	PlayTimeUpdate(now_anim_data);

	if(now_anim_data.play_time == now_anim_data.total_time)
	{
		is_end_ = TRUE;
	}
	else
	{
		is_end_ = FALSE;
	}
	BlendUpdate();

	ResetRequest();

}

void AnimatorBase::ChangeAnimation()
{

}

void AnimatorBase::PlayRequest(std::string name)
{
	// 同じリクエストはいれない
	for (auto& request_name : request_names_)
	{
		if (name == request_name) 
		{ 
			return;
		}
	}
	request_names_.push_back(name);
}

void AnimatorBase::LoadFile(const std::string file_path)
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
		std::string data;			// csvからの文字列をもらう
		std::string anim_name;
		std::string anim_file_path;
		std::string next_anim_name;
		int anim_index		= -1;
		int priority		= -1;
		int loop = -1;
		float play_speed	= 0.f;
		float cancel_time	= 0.f;
		AnimationData anim_data = {};


		// アニメーションの名前
		anim_name		= CSVFileAssistant::GetStringOfCSVFile(ss,data);  // アニメーションの名前 
		anim_file_path	= CSVFileAssistant::GetStringOfCSVFile(ss,data);  // アニメーションファイルの名前
		anim_index		= CSVFileAssistant::GetIntOfCSVFile(ss,data);	  // アニメーションの識別番号
		play_speed		= CSVFileAssistant::GetFloatOfCSVFile(ss,data);	  // アニメーションの再生速度
		priority		= CSVFileAssistant::GetIntOfCSVFile(ss,data);	  // アニメーションの優先度
		loop			= CSVFileAssistant::GetBoolOfCSVFile(ss,data);	  // ループするかどうか
		cancel_time		= CSVFileAssistant::GetFloatOfCSVFile(ss, data);  // animationのキャンセル可能時間
		next_anim_name	= CSVFileAssistant::GetStringOfCSVFile(ss, data); // 次のanimationのなまえ

		// アニメーションデータを生成
		LoadAnimation(anim_data, anim_file_path.c_str(), anim_index, play_speed, priority, cancel_time, loop, next_anim_name);
		animation_datas_[anim_name] = anim_data;
	}
}

void AnimatorBase::ResetRequest()
{
	request_names_.clear();
}

void AnimatorBase::Start()
{
	is_stop_ = FALSE;
}

void AnimatorBase::Stop()
{
	is_stop_ = TRUE;
}

void AnimatorBase::Cancel()
{
	can_cancel_ = TRUE;
}

const float AnimatorBase::GetPlayTime(std::string name) const
{
	float play_time = -1.f;

	auto data = animation_datas_.find(name);
	if (data == animation_datas_.end()) { return play_time; }

	play_time = data->second.play_time;

	return play_time;
}

const float AnimatorBase::GetTotalTime(std::string name) const
{
	float total_time = -1.f;

	auto data = animation_datas_.find(name);
	if (data == animation_datas_.end()) { return total_time; }

	total_time = data->second.total_time;
	return total_time;
}

const float AnimatorBase::GetRatio(std::string name) const
{
	float ratio = -1.f;
	auto data	= animation_datas_.find(name);

	if (data == animation_datas_.end()) { return ratio; }
	//if (name == data->first) { return ratio; }
	if (data->second.total_time == 0.f) { return ratio; }
	ratio = data->second.play_time / data->second.total_time;
	return ratio;
}

const bool AnimatorBase::GetIsBlending() const
{
	return is_blending_;
}

const std::string AnimatorBase::GetNowAnimName() const
{
	return now_anim_name_;
} 

const bool AnimatorBase::ChangeCondition() const
{
	if (now_anim_name_ == kNothing) { return TRUE; }
	if (next_anim_name_ == now_anim_name_) { return FALSE; }

	// チェンジできるか
	auto now_data = animation_datas_.find(now_anim_name_);
	auto next_data = animation_datas_.find(next_anim_name_);
	if (now_data == animation_datas_.end())	{ return FALSE; }
	if (next_data == animation_datas_.end())		{ return FALSE; }
	//if (is_blending_) { return FALSE; }
	// priorityが低くてもキャンセルが許されているときなら変更する
	if (next_data->second.priority <= now_data->second.priority) 
	{
		// キャンセルなら次に切り替えてok
		if (can_cancel_) { return TRUE; }
		
		// -1ならキャンセルできないようにする
		auto play_time		= now_data->second.play_time;
		auto cancel_time	= now_data->second.cancel_time;
		// キャンセルタムよりしたはだめ
		if (play_time < cancel_time) { return FALSE; }
	}

	return TRUE;
}

const bool AnimatorBase::CheckNextAnimation() const
{
	auto now_data = animation_datas_.find(now_anim_name_);
	if (now_data == animation_datas_.end()) { return FALSE; }
	if (now_data->second.next_anim_name == "nothing") { return FALSE; }
	if (!is_end_) { return FALSE; }
	return TRUE;
}

void AnimatorBase::PlayTimeUpdate(AnimationData& data)
{
	//stopじゃないときはアニメーションの再生を行う
	if (!is_stop_) { data.play_time += data.play_speed * FPS::GetInstance().GetDeltaTime() * 60.f; }

	// トータルタイムを超えた時
	if (data.play_time >= data.total_time)
	{
		if (data.loop)
		{
			data.play_time -= data.total_time;
		}
		else
		{
			data.play_time = data.total_time;
		}
	}
	MV1SetAttachAnimTime(handle_, data.attach_index,
		data.play_time);
}

void AnimatorBase::BlendUpdate()
{
	if (!is_blending_) { return; }
	auto& before_anim_data = animation_datas_[before_anim_name_];
	if (blend_rate_ >= 1.f) 
	{ 
		is_blending_	= FALSE;
		blend_rate_		= 1.f;
		//printfDx("now_anim		: %s\n", now_anim_name_.c_str());
		//printfDx("before_anim	: %s\n", before_anim_name_.c_str());
		MV1SetAttachAnimBlendRate(handle_, before_anim_data.attach_index, 1.f - blend_rate_);
		MV1SetAttachAnimBlendRate(handle_, animation_datas_[now_anim_name_].attach_index, blend_rate_);
		MV1DetachAnim(handle_, before_anim_data.attach_index);
		before_anim_data.attach_index	= -1;
		before_anim_data.play_time		= 0.f;
		return;
	}
	MV1SetAttachAnimBlendRate(handle_, before_anim_data.attach_index, 1.f - blend_rate_);
	MV1SetAttachAnimBlendRate(handle_, animation_datas_[now_anim_name_].attach_index, blend_rate_);
	blend_rate_ += FPS::GetInstance().GetDeltaTime() * 10.f;
}