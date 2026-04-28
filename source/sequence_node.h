#pragma once

class CompositeNode;

class SequenceNode : public CompositeNode
{
public:

	SequenceNode(std::vector<std::shared_ptr<NodeBase>> nodes);

	~SequenceNode() override;

	NodeStatus Update() override;

private:

	

};
