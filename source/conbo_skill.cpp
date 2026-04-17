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

ConboSkill::ConboSkill(std::weak_ptr<Player> owner,std::shared_ptr<BehaviorBase> behavior)
	: SkillBase(owner,behavior)
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
			return;
		}

		if (CheckGoNextConbo(conbo_action))
		{
			conbo_action->GoNext();
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