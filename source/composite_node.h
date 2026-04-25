#pragma once
#include"node_base.h"

class CompositeNode :public NodeBase
{
public:

	CompositeNode();

	virtual ~CompositeNode() override;

	void Update() override;

private:

	// •¡”‚Ì—Dæ‡ˆÊ‚Ì‚ ‚énode‚ğ‚Â
	std::map<int, std::shared_ptr<NodeBase>> nodes_;


};
