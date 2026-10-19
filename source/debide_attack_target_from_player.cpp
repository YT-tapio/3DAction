#include<memory>
#include<string>
#include<functional>
#include"DxLib.h"
#include"decide_attack_target_from_player.h"
#include"player_group_interface.h"
#include"object_base.h"

DecideAttackTargetFromPlayer::DecideAttackTargetFromPlayer(std::weak_ptr<ObjectBase> owner,std::shared_ptr<IPlayerGroup> player_group, std::function<void(std::string)> decide_target)
	: BehaviorBase(owner)
	, player_group_(player_group)
	, decide_target_(decide_target)
{

}

DecideAttackTargetFromPlayer::~DecideAttackTargetFromPlayer()
{

}

void DecideAttackTargetFromPlayer::Init()
{

}

void DecideAttackTargetFromPlayer::Entry()
{

}

BehaviorStatus DecideAttackTargetFromPlayer::Update()
{
	// ƒvƒŒƒCƒ„[‚Ìî•ñ‚ð‚à‚Æ‚É“G‚ÌUŒ‚‘ÎÛ‚ðŒˆ‚ß‚é
	if (auto owner = owner_.lock())
	{
		VECTOR owner_pos = owner->GetPosition();
		auto target_name = player_group_->MostNearPlayerName(owner_pos);
		if (decide_target_ != nullptr)
		{
			decide_target_(target_name);
			return BehaviorStatus::kComplete;
		}
	}
	return BehaviorStatus::kFailure;
}

void DecideAttackTargetFromPlayer::Exit()
{

}
