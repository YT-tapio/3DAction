#include<functional>
#include"DxLib.h"
#include"check_stamina.h"

CheckStamina::CheckStamina(std::function<float()> get_current_stamina, const float target_stamina)
	: IBehavior()
	, target_stamina_(target_stamina)
	, get_current_stamina_(get_current_stamina)
{

}

CheckStamina::~CheckStamina()
{

}

BehaviorStatus CheckStamina::Update()
{
	if (get_current_stamina_ == nullptr) { return BehaviorStatus::kFailure; }

	auto current_stamina = get_current_stamina_();

	return target_stamina_ <= current_stamina ? BehaviorStatus::kComplete : BehaviorStatus::kFailure;
}