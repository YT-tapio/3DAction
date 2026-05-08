#pragma once
#include"node_base.h"

class CompositeNode :public NodeBase
{
public:

	CompositeNode(std::vector<std::shared_ptr<NodeBase>> nodes);

	virtual ~CompositeNode() override;

	virtual void Init() override;

	virtual void Entry() override;

	BehaviorStatus Update() override;

	virtual void Exit() override;

	void Debug() override;

protected:

	// •¡”‚Ìnode‚ğ‚Â
	std::vector<std::shared_ptr<NodeBase>> nodes_;

	// Œ»İ‚Ìƒm[ƒh
	int current_node_;

private:

	

};
