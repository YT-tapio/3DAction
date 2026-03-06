#include<memory>
#include<map>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"player.h"
#include"animator_base.h"
#include"animation_data.h"
#include"animator_player.h"
#include"load_animation.h"
#include"fps.h"

AnimatorPlayer::AnimatorPlayer(int handle, std::shared_ptr<Player> player)
	: AnimatorBase("data/csv/animation/player/player_animation.csv",handle)
	, player_(player)
{

}

AnimatorPlayer::~AnimatorPlayer()
{

}


void AnimatorPlayer::Update()
{
	// とりあえずアタッチしましょう
	std::string before_anim_name = now_anim_name_;

	std::map<int, std::string,std::greater<int>> request_name_priority_mp;
	if (player_->GetIsMove()) { PlayRequest(kJogging); }
	if (player_->GetIsDash()) { PlayRequest(kRun); }
	if (player_->GetIsGround()) 
	{ 
		PlayRequest(kIdle);
	}
	
	if (!request_names_.empty()) 
	{ 
		for (auto& request_name : request_names_)
		{
			int priority = animation_datas_[request_name].priority;
			request_name_priority_mp[priority] = request_name;
		}
	}
	// requestの中でもpriorityのたかいものを取る。
	if (!request_name_priority_mp.empty()) { now_anim_name_ = request_name_priority_mp.begin()->second; }
	
	// 
	if (!animation_datas_[before_anim_name].loop && before_anim_name != kNothing)
	{
		// animationがすでに終わっているのかを見る
		if (!is_end_)
		{
			now_anim_name_ = before_anim_name;
		}
	}

	if (before_anim_name != now_anim_name_)
	{

		if (before_anim_name != kNothing)
		{
			MV1DetachAnim(handle_, animation_datas_[before_anim_name].anim_index);
		}

		animation_datas_[now_anim_name_].attach_index = MV1AttachAnim(handle_, animation_datas_[now_anim_name_].attach_index,
			animation_datas_[now_anim_name_].handle, FALSE);

		animation_datas_[now_anim_name_].total_time = MV1GetAttachAnimTotalTime(handle_, animation_datas_[now_anim_name_].attach_index);

		animation_datas_[now_anim_name_].play_time = 0.f;

		if (animation_datas_[now_anim_name_].attach_index == -1)	{ printfDx("アタッチに失敗しました\n"); }
		if (animation_datas_[now_anim_name_].total_time < 0.f)		{ printfDx("トータルおかしい\n"); }
	}
	animation_datas_[now_anim_name_].play_time += animation_datas_[now_anim_name_].play_speed * FPS::GetInstance().GetDeltaTime() * 60.f;
	if (animation_datas_[now_anim_name_].play_time >= animation_datas_[now_anim_name_].total_time) 
	{ 
		if(animation_datas_[now_anim_name_].loop)
		{
			animation_datas_[now_anim_name_].play_time -= animation_datas_[now_anim_name_].total_time;
		}
		else
		{
			animation_datas_[now_anim_name_].play_time = animation_datas_[now_anim_name_].total_time;
		}
		is_end_ = TRUE;
	}
	else
	{
		is_end_ = FALSE;
	}

	MV1SetAttachAnimTime(handle_, animation_datas_[now_anim_name_].attach_index,
		animation_datas_[now_anim_name_].play_time);

	ResetRequest();
}