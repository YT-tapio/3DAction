#pragma once
class ActionNode;

class AttackNode : public ActionNode
{
public:

	AttackNode();

	~AttackNode() override;

	BehaviorStatus Update() override;

private:



};