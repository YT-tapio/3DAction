#pragma once
#include"node_base.h"

class  EntryNode : public NodeBase
{
public:

	EntryNode();

	virtual ~EntryNode()override;

	virtual void Update() override;

private:

	std::unordered_map<int, NodeBase> nodes_;

};