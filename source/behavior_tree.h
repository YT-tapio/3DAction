#pragma once

class NodeBase;
class BehaviorTree
{
public:

	BehaviorTree(std::shared_ptr<NodeBase> node);

	~BehaviorTree();

	void Init();

	void Update();

	void Debug();

private:

	// start‚Ìnode‚ğ‚Â
	std::shared_ptr<NodeBase> node_;

};