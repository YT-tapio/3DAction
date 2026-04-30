#pragma once

class NodeBase;

class BranchNode :public NodeBase
{
public:

	BranchNode(std::pair<std::shared_ptr<NodeBase>, std::shared_ptr<NodeBase>>nodes,
		std::function<bool()> condition);

	~BranchNode() override;

	BehaviorStatus Update() override;

private:

	void function();

	// 子のノードは二つだけ
	// 関数ポインタが必要になってくる
	std::pair<std::shared_ptr<NodeBase>, std::shared_ptr<NodeBase>> nodes_;
	std::function<bool()> condition_;

};

/*
int index = 0;
	condition_ = [&index]()
		{

			return index;
		};
*/