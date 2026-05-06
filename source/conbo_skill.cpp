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
#include"FPS.h"

ConboSkill::ConboSkill(std::weak_ptr<Player> owner,std::shared_ptr<BehaviorBase> behavior, std::unordered_map<int, std::pair<float,float>> approach_speed_ratio_mp)
	: SkillBase(owner,behavior)
	, id_approach_speed_ratio_mp_(approach_speed_ratio_mp)
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
		Correction(conbo_action);
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
			//printfDx("change\n");
			VECTOR vel = VectorAssistant::VGetZero();
			Correction(conbo_action);
			//owner_.lock()->SetIsStop(TRUE);
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

void ConboSkill::Correction(std::shared_ptr<ConboAction> conbo_action)
{
	VECTOR vel = VectorAssistant::VGetZero();
	auto approach_speed_ratio_mp = id_approach_speed_ratio_mp_.find(conbo_action->GetCurrentConbo());	// 現在のコンボの補正値を受け取る
	if (approach_speed_ratio_mp == id_approach_speed_ratio_mp_.end()) { printfDx("おかしい\n"); return; }
	auto approach_speed_ratio = approach_speed_ratio_mp->second;	// speedとratioのでーた
	float approach_speed = approach_speed_ratio.first;		// speed
	float approach_ratio = approach_speed_ratio.second;	// ratio
	AttackCorrection::GetInstance().ApproachTheNearestEnemy(owner_.lock(), vel, approach_speed * FPS::GetInstance().GetDeltaTime() * 60.f, approach_ratio);
}

bool ConboSkill::IsStartConboAction(std::shared_ptr<ConboAction> conbo_action)
{
	auto owner = owner_.lock();
	
	if (is_active_)													{ return FALSE; }
	if (!owner->GetOnGround())								{ return FALSE; }
	if (owner->GetIsStop())									{ return FALSE; }
	//inputの確認
	if (!owner->GetInput()->IsStrongSkill()) { return FALSE; }

	return TRUE;
}

bool ConboSkill::CheckGoNextConbo(std::shared_ptr<ConboAction> conbo_action)
{
	auto owner = owner_.lock();
	if (!owner->GetOnGround()) { return FALSE; }
	if (!conbo_action->CheckNextConboReady()) { return FALSE; }
	//inputの確認
	if (!owner->GetInput()->IsStrongSkill()) { return FALSE; }

	return TRUE;
}