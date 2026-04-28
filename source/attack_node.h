#pragma once
class ActionNode;

class AttackNode : public ActionNode
{
public:

	AttackNode();

	~AttackNode() override;

	NodeStatus Update() override;

private:



};