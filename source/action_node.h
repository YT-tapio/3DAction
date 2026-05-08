#pragma once
#include"node_base.h"

#include"behavior_base.h"

class ActionNode : public NodeBase
{
public:

	ActionNode(std::shared_ptr<BehaviorBase> action);

	virtual ~ActionNode() override;
	
	virtual void Init() override;

	virtual void Entry() override;

	virtual BehaviorStatus Update() override;

	virtual void Exit() override;

	virtual void Debug() override;

private:

	// behavior‚ğ‚Â
	std::shared_ptr<BehaviorBase> action_;
	
};