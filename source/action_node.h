#pragma once
#include"node_base.h"

#include"behavior_base.h"

class ActionNode : public NodeBase
{
public:

	ActionNode();

	virtual ~ActionNode() override;
	
	virtual void Update() override;

private:

	// behavior‚ğ‚Â
	std::shared_ptr<BehaviorBase> action_;
	
};