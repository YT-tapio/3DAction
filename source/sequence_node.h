#pragma once

class CompositeNode;

class SequenceNode : public CompositeNode
{
public:

	SequenceNode();

	~SequenceNode() override;

	void Update() override;

private:

	

};
