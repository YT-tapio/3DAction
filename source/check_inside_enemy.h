#pragma once
#include"behavior_interface.h"


class CheckInsideEnemy : public IBehavior
{
public:

	CheckInsideEnemy();

	~CheckInsideEnemy() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

private:



};