#include<vector>
#include<memory>
#include"composite_node.h"
#include"sequence_node.h"
#include"node_status.h"

SequenceNode::SequenceNode(std::vector<std::shared_ptr<NodeBase>> nodes)
	: CompositeNode(nodes)
{

}

SequenceNode::~SequenceNode()
{

}

NodeStatus SequenceNode::Update()
{
	// 優先度の高いnodeから実行していく
	// sucsessの場合はループする

	while (current_node_ < nodes_.size())
	{
		auto status = nodes_[current_node_]->Update();

		switch (status)
		{
			//実行成功(終了)
		case NodeStatus::kSuccess:
			// 成功したら次のノードへ
			current_node_++;
			break;

			// 実行中
		case NodeStatus::kRunning:
			return NodeStatus::kRunning;
			break;

			// 実行失敗
		case NodeStatus::kFailure:
			current_node_ = 0;
			return NodeStatus::kFailure;
			break;
		}
	}
	// 全て成功なら成功を返す
	return NodeStatus::kSuccess;
}