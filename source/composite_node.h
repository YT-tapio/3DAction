#pragma once
#include"node_base.h"

class CompositeNode :public NodeBase
{
public:

	CompositeNode(std::vector<std::shared_ptr<NodeBase>> nodes);

	virtual ~CompositeNode() override;

	NodeStatus Update() override;

protected:

	// •¡”‚Ìnode‚ğ‚Â
	std::vector<std::shared_ptr<NodeBase>> nodes_;

	// Œ»İ‚Ìƒm[ƒh
	int current_node_;

private:

	

};
