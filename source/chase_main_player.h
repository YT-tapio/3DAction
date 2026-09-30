#pragma once
#include"behavior_interface.h"
#include"behavior_status.h"

class ChaseMainPlayer : public IBehavior
{
public:

	ChaseMainPlayer();

	~ChaseMainPlayer() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:


};