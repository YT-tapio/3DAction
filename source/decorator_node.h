#pragma once

class NodeBase;

class DecoratorNode : public NodeBase
{
public:

	DecoratorNode(std::unique_ptr<NodeBase> node_);

	~DecoratorNode() override;

	BehaviorStatus Update() override;

protected:

	std::unique_ptr<NodeBase> node_;

private:

	

};