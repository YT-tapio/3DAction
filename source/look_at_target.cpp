#include<memory>
#include"behavior_status.h"
#include"DxLib.h"
#include"look_at_target.h"
#include"condition_timer.h"
#include"variable_timer.h"
#include"vector_assistant.h"
#include<string>
#include"character_base.h"
#include"random.h"

LookAtTarget::LookAtTarget(std::weak_ptr<ObjectBase> owner,const float time)
	: BehaviorBase(owner)
	, timer_(std::make_shared<VariableTimer>())
	, base_time_(time)
{

}

LookAtTarget::~LookAtTarget()
{

}

void LookAtTarget::Init()
{

}

void LookAtTarget::Entry()
{
	timer_->Stop();
	float time = GetNormalRandom(base_time_, 0.7f);
	timer_->ChangeMaxTime(time);
	timer_->ReStart();
}

BehaviorStatus LookAtTarget::Update()
{
	timer_->Update();

	// ターゲットに体を向かす
	LookTarget();
	// タイマーが終わったらコンプリートを返す
	if (timer_->GetIsEnd())
	{
		return BehaviorStatus::kComplete;
	}

	return BehaviorStatus::kRunning;
}

void LookAtTarget::Exit()
{
	timer_->Stop();
}

void LookAtTarget::LookTarget()
{
	if (auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock()))
	{
		auto owner_pos = owner->GetPosition();
		auto target_pos = owner->GetAttackTargetPos();
		
		auto owner_to_target_dir = VectorAssistant::VGetDir(owner_pos, target_pos);

		auto rot_y = VectorAssistant::VGetTan(VectorAssistant::VGetReverce(VectorAssistant::VGetFlat(owner_to_target_dir)));
		auto rot = owner->GetRotation();
		rot.y = rot_y;
		owner->SetRotation(rot);
	}
}
