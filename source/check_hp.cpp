#include<memory>
#include"check_hp.h"
#include"behavior_status.h"

CheckHp::CheckHp(float* hp, const float target_hp)
	: IBehavior()
	,target_hp_(target_hp)
	,hp_(hp)
{

}

CheckHp::~CheckHp()
{

}

BehaviorStatus CheckHp::Update()
{
	if (*hp_ > 0) { return BehaviorStatus::kComplete; }
	return BehaviorStatus::kFailure;
}