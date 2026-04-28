#pragma once

class CompositeNode;

class SequenceNode : public CompositeNode
{
public:

	SequenceNode(std::map<int, std::shared_ptr<NodeBase>, std::greater<int>> nodes);

	~SequenceNode() override;

	NodeStatus Update() override;

private:

	

};
