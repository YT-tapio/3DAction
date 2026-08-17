#pragma once
#include"action_node.h"

class JustOneNode : public ActionNode
{
public:

	JustOneNode(std::shared_ptr<BehaviorBase> action);

	virtual ~JustOneNode() override;

	virtual BehaviorStatus Update() override;

private:

	bool is_finished_;


};
