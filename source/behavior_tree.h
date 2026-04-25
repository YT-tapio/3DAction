#pragma once

class NodeBase;
class BehaviorTree
{
public:

	BehaviorTree();

	~BehaviorTree();

	void Update();

private:

	// start‚Ìnode‚ğ‚Â
	std::shared_ptr<NodeBase> node_;

};