#pragma once

class CompositeNode;

class SelectorNode : public CompositeNode
{
public:

	SelectorNode(std::vector<std::shared_ptr<NodeBase>> nodes);

	~SelectorNode();

	BehaviorStatus Update();

private:


};
