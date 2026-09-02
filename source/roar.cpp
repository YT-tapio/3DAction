#include<memory>
#include"roar.h"
#include<string>
#include"character_base.h"
#include<unordered_map>
#include"animator_base.h"
#include"sound_manager.h"

Roar::Roar(std::shared_ptr<ObjectBase> owner)
	: BehaviorBase(owner)
	, is_character_(FALSE)
{
	if (auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock()))
	{
		is_character_ = TRUE;
	}
}

Roar::~Roar()
{

}

void Roar::Entry()
{
	//printfDx("roar\n");
	if (!is_character_) { return; }
	auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	owner->GetAnimator()->PlayRequest("roar");
	SoundManager::GetInstance().SetPos("tackle_vioce", owner->GetPosition());
	SoundManager::GetInstance().Play3DSound("tackle_voice");
}

BehaviorStatus Roar::Update()
{
	// roar‚ªI—¹‚µ‚½‚çŠ®—¹‚ğ•Ô‚·
	if (!is_character_) { return BehaviorStatus::kFailure; }
	auto owner = std::dynamic_pointer_cast<CharacterBase>(owner_.lock());
	if (owner->GetAnimator()->GetIsEnd("roar"))
	{
		return BehaviorStatus::kComplete;
	}
	return BehaviorStatus::kRunning;
}

void Roar::Exit()
{

}