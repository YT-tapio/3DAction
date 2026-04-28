#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include<vector>
#include"DxLib.h"
#include"conbo.h"
#include"object_base.h"
#include"character_base.h"
#include"animator_base.h"
#include"behavior_status.h"

Conbo::Conbo(std::weak_ptr<ObjectBase> owner,float min_ratio, float max_ratio, float go_next_timing, std::string my_anim_name, std::shared_ptr<BehaviorBase> behavior)
	: BehaviorBase(owner)
	, behavior_(behavior)
	, min_ratio_(min_ratio)
	, max_ratio_(max_ratio)
	, go_next_timing_(go_next_timing)
	, my_anim_name_(my_anim_name)
{
	
}

Conbo::~Conbo()
{

}

void Conbo::Init()
{
	behavior_->Init();
}

BehaviorStatus Conbo::Update()
{
	return behavior_->Update();
}

void Conbo::Exit()
{
	behavior_->Exit();
}

void Conbo::Draw()
{
	behavior_->Draw();
}

void Conbo::Debug()
{
	behavior_->Debug();
}

const bool Conbo::CheckNextReady() const
{
	auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	
	if (owner == nullptr) { return FALSE; }
	auto animator	= owner->GetAnimator();
	float ratio		= animator->GetRatio(my_anim_name_);

	if (ratio < min_ratio_) { return FALSE; }
	if (ratio > max_ratio_) { return FALSE; }
	return TRUE;
}

const bool Conbo::CheckAnimation() const
{
	const float kLastConboTiming = 1.f;
	auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	if (owner == nullptr) { return FALSE; }	//•ÏŠ·
	auto animator = owner->GetAnimator();
	float ratio = animator->GetRatio(my_anim_name_);
	if (go_next_timing_ == kLastConboTiming) { return FALSE; }
	if (0 > ratio)						{ return FALSE; }
	if (ratio < go_next_timing_) { return FALSE; }
	return TRUE;
}

const bool Conbo::CheckIsEnd() const
{
	auto character = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	if (character == nullptr) { return FALSE; }
	if (character->GetAnimator()->GetNowAnimName() == my_anim_name_) { return FALSE; }
	return TRUE;
}

const std::string Conbo::GetMyAnimName() const
{
	return my_anim_name_;
}