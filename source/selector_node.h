#pragma once

class CompositeNode;

class SelectorNode : public CompositeNode
{
public:

	SelectorNode(std::vector<std::shared_ptr<NodeBase>> nodes);

	~SelectorNode();

	NodeStatus Update();

private:


};
