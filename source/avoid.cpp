#include<memory>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"avoid.h"
#include"object_base.h"
#include"character_base.h"
#include"animator_base.h"
#include"behavior_status.h"
Avoid::Avoid(std::weak_ptr<ObjectBase> owner)
	: BehaviorBase(owner)
{
	my_anim_name_ = "avoid";
}

Avoid::~Avoid()
{

}

void Avoid::Init()
{

}

BehaviorStatus Avoid::Update()
{
	// animationの時間によってcharacterを無敵にする

	std::shared_ptr<CharacterBase> chara = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());

	// 変換できない場合は早期リターン
	if (chara == nullptr)
	{
		printfDx("こいつには行動を付与できません");
		return BehaviorStatus::kFailure;
	}

	//自分の行動を起こせるanimationかをチェック
	if (chara->GetAnimator()->GetNowAnimName() != my_anim_name_) 
	{
		chara->SetInvincible(FALSE);
		return BehaviorStatus::kFailure;
	}

	float now_play_time_ = chara->GetAnimator()->GetPlayTime(my_anim_name_);

	// animationの時間によって無敵にするかどうかを判断
	
	if (now_play_time_ > 0 && now_play_time_ < chara->GetAnimator()->GetTotalTime("avoid"))
	{ 
		chara->SetInvincible(TRUE);
		return BehaviorStatus::kRunning;
	}
	else
	{
		chara->SetInvincible(FALSE);
		return BehaviorStatus::kSuccess;
	}
	return BehaviorStatus::kSuccess;
}

void Avoid::Debug()
{

}
