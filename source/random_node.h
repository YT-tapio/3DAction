#pragma once

class NodeBase;
class CompositeNode;
enum class BehaviorStatus;

class RandomNode :public CompositeNode
{
public:

	RandomNode(std::vector<std::shared_ptr<NodeBase>> nodes);

	~RandomNode() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Debug() override;

private:
	
	BehaviorStatus status_;
};