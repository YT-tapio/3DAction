#pragma once
#include"behavior_base.h"

class IPlayerGroup;

//プレイヤーの中からターゲットを選択
class DecideAttackTargetFromPlayer : public BehaviorBase
{
public:

	DecideAttackTargetFromPlayer(std::weak_ptr<ObjectBase> owner, std::shared_ptr<IPlayerGroup> player_group,std::function<void(std::string)> decide_target);

	~DecideAttackTargetFromPlayer() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:
	
	std::shared_ptr<IPlayerGroup> player_group_;
	std::function<void(std::string)> decide_target_;

};