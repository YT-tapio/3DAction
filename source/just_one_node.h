#pragma once
#include"action_node.h"

class JustOneNode : public NodeBase
{
public:

	JustOneNode();

	virtual ~JustOneNode() override;

	void Entry() override;

	virtual BehaviorStatus Update() override;

	void Exit() override;

private:

	bool is_finished_;


};
