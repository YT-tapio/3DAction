#include<memory>
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
	now_anim_name_ = "jogging";
	VECTOR pos = player_->GetPosition();
	if (CheckHitKey(KEY_INPUT_0)) { now_anim_name_ = "idle"; }
	if (CheckHitKey(KEY_INPUT_1)) { now_anim_name_ = "run"; }
	printfDx("x : %.2f,y : %.2f,z : %.2f\n", pos.x, pos.y, pos.z);
	if (before_anim_name != now_anim_name_)
	{
		printfDx("%d\n", animation_datas_.size());
		if (before_anim_name != "nothing")
		{
			MV1DetachAnim(handle_, animation_datas_[before_anim_name].anim_index);
		}

		animation_datas_[now_anim_name_].attach_index = MV1AttachAnim(handle_, animation_datas_[now_anim_name_].attach_index,
			animation_datas_[now_anim_name_].handle, FALSE);

		printfDx("%d\n", animation_datas_.size());

		animation_datas_[now_anim_name_].total_time = MV1GetAttachAnimTotalTime(handle_, animation_datas_[now_anim_name_].attach_index);

		animation_datas_[now_anim_name_].play_time = 0.f;

		if (animation_datas_[now_anim_name_].attach_index == -1)	{ printfDx("アタッチに失敗しました\n"); }
		if (animation_datas_[now_anim_name_].total_time < 0.f)		{ printfDx("トータルおかしい\n"); }

	}
	animation_datas_[now_anim_name_].play_time += animation_datas_[now_anim_name_].play_speed * FPS::GetInstance().GetDeltaTime() * 60.f;
	if (animation_datas_[now_anim_name_].play_time > animation_datas_[now_anim_name_].total_time) 
	{ 
		animation_datas_[now_anim_name_].play_time -= animation_datas_[now_anim_name_].total_time;
	}
	MV1SetAttachAnimTime(handle_, animation_datas_[now_anim_name_].attach_index,
		animation_datas_[now_anim_name_].play_time);
	
}