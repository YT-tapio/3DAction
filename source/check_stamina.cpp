#include"DxLib.h"
#include"check_stamina.h"

CheckStamina::CheckStamina(float* current_stamina,const float target_stamina)
	: IBehavior()
	, target_stamina_(target_stamina)
	, current_stamina_(*current_stamina)
{

}

CheckStamina::~CheckStamina()
{

}

BehaviorStatus CheckStamina::Update()
{
	return target_stamina_ <= current_stamina_ ? BehaviorStatus::kComplete : BehaviorStatus::kFailure;
}