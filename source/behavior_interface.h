#pragma once
#include"behavior_status.h"

class IBehavior
{
public:

	virtual ~IBehavior() = default;

	virtual void Init() = 0;

	virtual void Entry() = 0;

	virtual BehaviorStatus Update() = 0;

	virtual void Exit() = 0;

	virtual void Draw() = 0;

	virtual void Debug() = 0;
};