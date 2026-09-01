#pragma once
#include"node_base.h"

class CheckCountNode : public NodeBase
{
public:

	CheckCountNode(const int& target_count);

	~CheckCountNode() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;


private:

	int target_count_;
	int current_count_;

};
