#include<vector>
#include<memory>
#include"DxLib.h"
#include"composite_node.h"
#include"sequence_node.h"
#include"behavior_status.h"

SequenceNode::SequenceNode(std::vector<std::shared_ptr<NodeBase>> nodes)
	: CompositeNode(nodes)
{

}

SequenceNode::~SequenceNode()
{

}

BehaviorStatus SequenceNode::Update()
{
	// 優先度の高いnodeから実行していく
	// sucsessの場合はループする

	while (current_node_ < nodes_.size())
	{
		auto status = nodes_[current_node_]->Update();

		switch (status)
		{
			//実行成功(終了)
		case BehaviorStatus::kComplete:
			nodes_[current_node_]->Exit();	//
			// 成功したら次のノードへ
			current_node_++;
			if (current_node_ < nodes_.size())
			{
				nodes_[current_node_]->Entry();
			}
			else
			{
				current_node_ = nodes_.size() - 1;	// 最後のnodeに
				return BehaviorStatus::kComplete;
			}
			break;

			// 実行中
		case BehaviorStatus::kRunning:
			return BehaviorStatus::kRunning;
			break;

			// 実行失敗
		case BehaviorStatus::kFailure:
			nodes_[current_node_]->Exit();
			current_node_ = 0;
			nodes_[current_node_]->Entry();
			return BehaviorStatus::kFailure;
			break;
		}
	}

	// 全て成功なら成功を返す
	return BehaviorStatus::kComplete;
}