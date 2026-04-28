#pragma once

class NodeBase;

class DecoratorNode : public NodeBase
{
public:

	DecoratorNode();

	~DecoratorNode() override;

	NodeStatus Update() override;

private:



};