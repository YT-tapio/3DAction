#include<memory>
#include<string>
#include"DxLib.h"
#include"attack_base.h"
#include"tackle.h"
#include"roar_tackle.h"
#include"behavior_status.h"
#include"character_base.h"
#include<list>
#include<unordered_map>
#include"animator_base.h"
#include<functional>
#include"vector_assistant.h"
#include"attack_range_group_interface.h"

RoarTackle::RoarTackle(std::weak_ptr<ObjectBase> owner, std::shared_ptr<RigidBody> rigid_body,
	std::string anim_name, const float time, const float speed, float damage_rate,std::shared_ptr<IAttackRangeGroup> attack_range_group)
	: Tackle(owner,rigid_body,anim_name,time,speed,damage_rate)
	, tackle_state_(TackleState::roar)
	, roar_anim_name_("")
	, attack_range_ui_id_(-1)
	, attack_dir_(VectorAssistant::VGetZero())
	, is_end_(FALSE)
	, attack_range_group_(attack_range_group)
{

}

RoarTackle::~RoarTackle()
{

}

void RoarTackle::Init()
{
	Tackle::Init();
}

void RoarTackle::Entry()
{
	//printfDx("叫び＆突進\n");
	tackle_state_ = TackleState::roar;
	is_end_ = FALSE;
	float max_time = 0.f;
	if (auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock()))
	{
		owner->GetAnimator()->PlayRequest("charge_tackle");
		VECTOR attack_target_pos = owner->GetAttackTargetPos();
		attack_dir_ = VectorAssistant::VGetDir(owner->GetPosition(), attack_target_pos);
		max_time = 1.96f;//owner->GetAnimator()->GetFPSTotalTime("charge_tacle");
	}
	std::function<bool()> end_function = [this]()
		{
			return is_end_;
		};

	attack_range_ui_id_ = attack_range_group_->RectangleDrawRequest(owner_.lock()->GetPosition(), VGet(8.5f,1.f,57.f), attack_dir_, max_time,end_function);
}

BehaviorStatus RoarTackle::Update()
{
	
	switch (tackle_state_)
	{
	case TackleState::roar:
		RoarUpdate();
		break;

	case TackleState::tackle:
		auto state = TackleUpdate();
		if (state == BehaviorStatus::kComplete) { is_end_ = TRUE; }
		return state;
		break;
	}

	return BehaviorStatus::kRunning;
}

void RoarTackle::Exit()
{

}

void RoarTackle::RoarUpdate()
{
	VECTOR owner_pos = owner_.lock()->GetPosition();
	// アニメーションが終わったら次のアニメーション(タックル) 
	if (auto character = std::dynamic_pointer_cast<CharacterBase>(owner_.lock()))
	{
		if (character->GetAnimator()->GetIsEnd("charge_tackle"))
		{
			// 終了したら次へ
			tackle_state_ = TackleState::tackle;
			Tackle::Entry();
		}
		VECTOR attack_target_pos = character->GetAttackTargetPos();
		attack_dir_ = VectorAssistant::VGetDir(character->GetPosition(), attack_target_pos);
	}
	attack_range_group_->RectangleSetDir(attack_range_ui_id_, attack_dir_);
	attack_range_group_->RectangleSetPos(attack_range_ui_id_, owner_pos);
}

BehaviorStatus RoarTackle::TackleUpdate()
{
	return Tackle::Update();
}