#pragma once
#include"node_base.h"

class ConditionTimer;

class WaitNode : public NodeBase
{
public:

	WaitNode(std::shared_ptr<NodeBase> node,const float time = 1.f);

	~WaitNode() override;

	virtual void Init() override;

	virtual void Entry() override;

	virtual BehaviorStatus Update() override;

	virtual void Exit() override;

	virtual void Debug() override;


private:

	std::shared_ptr<NodeBase> node_;
	std::shared_ptr<ConditionTimer> timer_;
};