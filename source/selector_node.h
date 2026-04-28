#pragma once

class CompositeNode;

class SelectorNode : public CompositeNode
{
public:

	SelectorNode(std::map<int, std::shared_ptr<NodeBase>, std::greater<int>> nodes);

	~SelectorNode();

	NodeStatus Update();

private:


};
