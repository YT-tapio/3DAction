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

Conbo::Conbo(float min_ratio, float max_ratio, std::string my_anim_name, std::shared_ptr<BehaviorBase> behavior, std::weak_ptr<ObjectBase> owner)
	: BehaviorBase(owner)
	, behavior_(behavior)
	, min_ratio_(min_ratio)
	, max_ratio_(max_ratio)
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

void Conbo::Update()
{
	behavior_->Update();
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