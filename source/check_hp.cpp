#include<memory>
#include"check_hp.h"
#include"behavior_status.h"

CheckHp::CheckHp(std::shared_ptr<ObjectBase> owner,float* hp)
	: BehaviorBase(owner)
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