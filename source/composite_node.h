#pragma once
#include"node_base.h"

class CompositeNode :public NodeBase
{
public:

	CompositeNode(std::map<int, std::shared_ptr<NodeBase>, std::greater<int>> nodes);

	virtual ~CompositeNode() override;

	NodeStatus Update() override;

private:

	// •¡”‚Ì—Dæ‡ˆÊ‚Ì‚ ‚énode‚ğ‚Â
	std::map<int, std::shared_ptr<NodeBase>,std::greater<int>> nodes_;

};
