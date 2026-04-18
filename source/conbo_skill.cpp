#include<fstream>
#include<sstream>
#include<string>
#include<memory>
#include<unordered_map>
#include<vector>
#include"DxLib.h"
#include"conbo_skill.h"
#include"object_base.h"
#include"conbo_action.h"
#include"player.h"
#include"behavior_base.h"
#include"animator_base.h"
#include"input_base.h"
#include"attack_correction.h"
#include"vector_assistant.h"


ConboSkill::ConboSkill(std::weak_ptr<Player> owner,std::shared_ptr<BehaviorBase> behavior,float approach_speed, float approach_ratio)
	: SkillBase(owner,behavior)
	, approach_speed_(approach_speed)
	, approach_ratio_(approach_ratio)
{

}

ConboSkill::~ConboSkill()
{
	
}

void ConboSkill::Init()
{
	behavior_->Init();
}

void ConboSkill::Update()
{
	// behaviorをconboに変換する必要がある
	auto conbo_action = std::dynamic_pointer_cast<ConboAction>(behavior_);
	if (conbo_action == nullptr) { return; }
	bool is_attack = FALSE;

	if (IsStartConboAction(conbo_action))
	{
		is_active_ = TRUE;
		owner_.lock()->GetAnimator()->PlayRequest(conbo_action->GetFirstConboAnimation());
		owner_.lock()->SetIsStop(TRUE);
		is_attack = TRUE;
		VECTOR vel = VectorAssistant::VGetZero();
		AttackCorrection::GetInstance().ApproachTheNearestEnemy(owner_.lock(), vel, 18.5f, 0.3f);
	}

	if (is_active_)
	{
		// コンボが終了したかの判断
		if (conbo_action->CheckIsEnd())
		{
			if (is_attack) { return; }
			is_active_ = FALSE;
			conbo_action->Exit();
			owner_.lock()->SetIsStop(FALSE);
			// ここでcool_timeを開始

			return;
		}

		if (CheckGoNextConbo(conbo_action))
		{
			conbo_action->GoNext();
		}

		if (conbo_action->CheckChangeConbo())
		{
			// ここで補正が発生する
			printfDx("change\n");
			VECTOR vel = VectorAssistant::VGetZero();
			AttackCorrection::GetInstance().ApproachTheNearestEnemy(owner_.lock(), vel, 18.5f, 0.3f);
		}

	}

	behavior_->Update();
}

void ConboSkill::Draw()
{

}

void ConboSkill::Debug()
{
	behavior_->Debug();
}

bool ConboSkill::IsStartConboAction(std::shared_ptr<ConboAction> conbo_action)
{
	auto owner = owner_.lock();
	
	if (is_active_)													{ return FALSE; }
	if (!owner->GetIsGround())								{ return FALSE; }
	if (owner->GetIsStop())									{ return FALSE; }
	//inputの確認
	if (!owner->GetInput()->IsStrongSkill()) { return FALSE; }

	return TRUE;
}

bool ConboSkill::CheckGoNextConbo(std::shared_ptr<ConboAction> conbo_action)
{
	auto owner = owner_.lock();
	if (!owner->GetIsGround()) { return FALSE; }
	if (!conbo_action->CheckNextConboReady()) { return FALSE; }
	//inputの確認
	if (!owner->GetInput()->IsStrongSkill()) { return FALSE; }

	return TRUE;
}