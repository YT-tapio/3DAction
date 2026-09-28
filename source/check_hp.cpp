#include<memory>
#include"check_hp.h"
#include"behavior_status.h"

CheckHp::CheckHp(float* hp)
	: IBehavior()
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