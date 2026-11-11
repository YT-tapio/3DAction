#pragma once
#include"behavior_interface.h"
#include"behavior_status.h"

class AIInput;

class ChaseMainPlayer : public IBehavior
{
public:

	ChaseMainPlayer(AIInput* input,std::function<VECTOR()> get_onwer_pos, std::function<VECTOR()> get_main_player_pos);

	~ChaseMainPlayer() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:

	std::function<VECTOR()> get_owner_pos_;
	std::function<VECTOR()> get_main_player_pos_;

	AIInput* input_;

};