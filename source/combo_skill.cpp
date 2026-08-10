#include<fstream>
#include<sstream>
#include<string>
#include<memory>
#include<unordered_map>
#include<vector>
#include"DxLib.h"
#include"combo_skill.h"
#include"object_base.h"
#include"combo_action.h"
#include"player.h"
#include"behavior_base.h"
#include"animator_base.h"
#include"input_base.h"
#include"attack_correction.h"
#include"vector_assistant.h"
#include"FPS.h"
#include"time.h"
#include"skill_name.h"
#include"sound_manager.h"

ComboSkill::ComboSkill(std::weak_ptr<Player> owner,std::shared_ptr<BehaviorBase> behavior, std::unordered_map<int, std::pair<float,float>> approach_speed_ratio_mp,SkillType type, float cool_time)
	: SkillBase(owner,behavior, type, cool_time)
	, id_approach_speed_ratio_mp_(approach_speed_ratio_mp)
{

}

ComboSkill::~ComboSkill()
{
	
}

void ComboSkill::Init()
{
	behavior_->Init();
}

void ComboSkill::Update()
{
	// behaviorをcomboに変換する必要がある
	auto combo_action = std::dynamic_pointer_cast<ComboAction>(behavior_);
	if (combo_action == nullptr) { return; }
	bool is_attack = FALSE;
	
	if (!can_use_)
	{
		cool_time_->Update();
		if (cool_time_->GetIsEnd())
		{
			//printfDx("終了\n");
			can_use_ = TRUE;
		}
		
	}

	if (IsStartcomboAction(combo_action))
	{
		is_active_ = TRUE;
		owner_.lock()->GetAnimator()->PlayRequest(combo_action->GetFirstcomboAnimation());
		owner_.lock()->SetIsStop(TRUE);
		is_attack = TRUE;
		Correction(combo_action);
		cool_time_->ReSet();
		can_use_ = FALSE;
		SoundManager::GetInstance().Play2DSound("approach_enemy");
	}
	// printfDx("%.2f\n", cool_time_->GetRatio());
	if (is_active_)
	{
		// コンボが終了したかの判断
		if (combo_action->CheckIsEnd())
		{
			if (is_attack) { return; }
			is_active_ = FALSE;
			combo_action->Exit();
			owner_.lock()->SetIsStop(FALSE);
			// ここでcool_timeを開始
			cool_time_->ReStart();
			//printfDx("変化");
			return;
		}

		if (CheckGoNextcombo(combo_action))
		{
			combo_action->GoNext();
		}
		
		if (combo_action->CheckChangeCombo())
		{
			// ここで補正が発生する
			//printfDx("change\n");
			VECTOR vel = VectorAssistant::VGetZero();
			Correction(combo_action);
			SoundManager::GetInstance().Play2DSound("approach_enemy");
			//owner_.lock()->SetIsStop(TRUE);
		}
	}

	behavior_->Update();
}

void ComboSkill::Draw()
{

}

void ComboSkill::Debug()
{
	behavior_->Debug();
}

void ComboSkill::Correction(std::shared_ptr<ComboAction> combo_action)
{
	VECTOR vel = VectorAssistant::VGetZero();
	auto approach_speed_ratio_mp = id_approach_speed_ratio_mp_.find(combo_action->GetCurrentcombo());	// 現在のコンボの補正値を受け取る
	if (approach_speed_ratio_mp == id_approach_speed_ratio_mp_.end()) { printfDx("おかしい\n"); return; }
	auto approach_speed_ratio = approach_speed_ratio_mp->second;	// speedとratioのでーた
	float approach_speed = approach_speed_ratio.first;		// speed
	float approach_ratio = approach_speed_ratio.second;	// ratio
	AttackCorrection::GetInstance().ApproachTheNearestEnemy(owner_.lock(), vel, approach_speed * owner_.lock()->GetTime()->GetFPSRate(), approach_ratio);
}

bool ComboSkill::IsStartcomboAction(std::shared_ptr<ComboAction> combo_action)
{
	auto owner = owner_.lock();
	
	if (!can_use_)											{ return FALSE; }
	if (is_active_)											{ return FALSE; }
	if (!owner->GetOnGround())								{ return FALSE; }
	if (!owner->GetCanMove()) { return FALSE; }
	if (owner->GetIsStop())									{ return FALSE; }
	//inputの確認
	if (!PushMyType()) { return FALSE; }

	return TRUE;
}

bool ComboSkill::CheckGoNextcombo(std::shared_ptr<ComboAction> combo_action)
{
	auto owner = owner_.lock();
	if (!owner->GetOnGround()) { return FALSE; }
	if (!combo_action->CheckNextcomboReady()) { return FALSE; }
	//inputの確認
	if (!PushMyType()) { return FALSE; }

	return TRUE;
}

const int ComboSkill::GetID() const
{
	return SkillName::kComboAttack;
}