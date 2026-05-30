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
	before_anim_name_ = now_anim_name_;
	// もし次に続くアニメーションがあるなら
	if (CheckNextAnimation())
	{
		PlayRequest(animation_datas_[now_anim_name_].next_anim_name);
	}

	// リクエストの整理をする
	ChangeAnimation();
	
	// アニメーションを続ける
	if (ContinueCondition())
	{
		now_anim_name_ = before_anim_name_;
	}
	auto now_anim_data = animation_datas_[now_anim_name_];

	// animationのアタッチ
	if (before_anim_name_ != now_anim_name_)
	{
		// キャンセルを無効にする
		can_cancel_		= FALSE;
		is_end_			= FALSE;
		is_blending_	= TRUE;	// 何もないとブレンドしない
		blend_rate_		= 0.f;
		
		if (before_anim_name_ == kNothing)
		{
			is_blending_ = FALSE;
		}

		// アタッチ
		now_anim_data.attach_index = MV1AttachAnim(handle_, now_anim_data.anim_index,
			now_anim_data.handle, FALSE);

		// トータルタイムを取得
		now_anim_data.total_time = MV1GetAttachAnimTotalTime(handle_, now_anim_data.attach_index);

		now_anim_data.play_time = 0.f;

		if (now_anim_data.attach_index == -1) { printfDx("アタッチに失敗しました\n"); }
		if (now_anim_data.total_time < 0.f) { printfDx("トータルおかしい\n"); }
	}

	//stopじゃないときはアニメーションの再生を行う
	if(!is_stop_){ now_anim_data.play_time += now_anim_data.play_speed * FPS::GetInstance().GetDeltaTime() * 60.f; }

	// トータルタイムを超えた時
	if (now_anim_data.play_time >= now_anim_data.total_time)
	{
		if (now_anim_data.loop)
		{
			now_anim_data.play_time -= now_anim_data.total_time;
		}
		else
		{
			now_anim_data.play_time = now_anim_data.total_time;
			is_end_ = TRUE;
		}
	}
	else
	{
		is_end_ = FALSE;
	}

	MV1SetAttachAnimTime(handle_, now_anim_data.attach_index,
		now_anim_data.play_time);
	BlendUpdate();

	ResetRequest();

}

void AnimatorBase::ChangeAnimation()
{

}

void AnimatorBase::PlayRequest(std::string name)
{
	// 今流しているアニメーション(ループなし)と同じなら除去
	if (now_anim_name_ == name)
	{
		/*
		if (const auto request_data = animation_datas_.find(name);request_data != animation_datas_.end())
		{
			if (!request_data->second.loop) { return; }
		}
		*/
		
	}
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

const std::string AnimatorBase::GetNowAnimName() const
{
	return now_anim_name_;
} 

const bool AnimatorBase::ContinueCondition() const
{
	if (before_anim_name_ == kNothing) { return FALSE; }
	if (now_anim_name_ == before_anim_name_) { return FALSE; }

	// チェンジできるか
	auto before_data = animation_datas_.find(before_anim_name_);
	auto now_data = animation_datas_.find(now_anim_name_);
	if (before_data == animation_datas_.end())	{ return FALSE; }
	if (now_data == animation_datas_.end())		{ return FALSE; }
	if (before_data->second.loop){ return FALSE; }

	if (is_end_) { return FALSE; }

	// priorityが低くてもキャンセルが許されているときなら変更する
	if (before_data->second.priority <= now_data->second.priority) 
	{ 
		if (!can_cancel_) { return FALSE; }
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

void AnimatorBase::BlendUpdate()
{
	if (!is_blending_) { return; }
	
	// ブレンドします
	//stopじゃないときはアニメーションの再生を行う
	auto before_anim_data = animation_datas_[before_anim_name_];
	if (!is_stop_) { before_anim_data.play_time += before_anim_data.play_speed * FPS::GetInstance().GetDeltaTime() * 60.f; }

	// トータルタイムを超えた時
	if (before_anim_data.play_time >= before_anim_data.total_time)
	{
		if (before_anim_data.loop)
		{
			before_anim_data.play_time -= before_anim_data.total_time;
		}
		else
		{
			before_anim_data.play_time = before_anim_data.total_time;
		}
	}

	MV1SetAttachAnimTime(handle_, before_anim_data.attach_index,
		before_anim_data.play_time);
	
	if (blend_rate_ >= 1.f) 
	{ 
		is_blending_	= FALSE;
		blend_rate_		= 1.f;

		MV1DetachAnim(handle_, before_anim_data.attach_index);
		before_anim_data.attach_index	= -1;
		before_anim_data.play_time		= 0.f;
		return;
	}
	
	MV1SetAttachAnimBlendRate(handle_, before_anim_data.attach_index, 1.f - blend_rate_);
	MV1SetAttachAnimBlendRate(handle_, animation_datas_[now_anim_name_].attach_index, blend_rate_);
	blend_rate_ += FPS::GetInstance().GetDeltaTime() * 3.f;
}