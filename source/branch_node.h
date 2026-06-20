#pragma once

class NodeBase;
enum class BehaviorStatus;

class BranchNode :public NodeBase
{
public:

	BranchNode(std::pair<std::shared_ptr<NodeBase>, std::shared_ptr<NodeBase>>nodes,
		std::function<bool()> condition);

	~BranchNode() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Debug() override;

private:

	void function();

	// 子のノードは二つだけ
	// 関数ポインタが必要になってくる
	std::pair<std::shared_ptr<NodeBase>, std::shared_ptr<NodeBase>> nodes_;
	std::function<bool()> condition_;
	
	bool is_first_update_;
};

/*
int index = 0;
	condition_ = [&index]()
		{

			return index;
		};
*/