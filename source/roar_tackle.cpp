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
#include"attack_range_group.h"
#include"vector_assistant.h"

RoarTackle::RoarTackle(std::weak_ptr<ObjectBase> owner, std::shared_ptr<RigidBody> rigid_body,
	std::string anim_name, const float time, const float speed, float damage_rate)
	: Tackle(owner,rigid_body,anim_name,time,speed,damage_rate)
	, tackle_state_(TackleState::roar)
	, roar_anim_name_("")
	, attack_range_ui_id_(-1)
	, attack_dir_(VectorAssistant::VGetZero())
	, is_end_(FALSE)
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
	tackle_state_ = TackleState::roar;
	is_end_ = FALSE;
	if (auto character = std::dynamic_pointer_cast<CharacterBase>(owner_.lock()))
	{
		character->GetAnimator()->PlayRequest("charge_tackle");
		VECTOR attack_target_pos = character->GetAttackTargetPos();
		attack_dir_ = VectorAssistant::VGetDir(character->GetPosition(), attack_target_pos);
	}
	std::function<bool()> end_function = [this]()
		{
			return is_end_;
		};
	attack_range_ui_id_ = AttackRangeGroup::GetInstance().RectangleDrawRequest(owner_.lock()->GetPosition(), VGet(0.1f,1.f,1.f), attack_dir_, end_function);
	
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

	AttackRangeGroup::GetInstance().RectangleSetDir(attack_range_ui_id_, attack_dir_);
}

BehaviorStatus RoarTackle::TackleUpdate()
{
	return Tackle::Update();
}