#include<vector>
#include<memory>
#include"composite_node.h"
#include"selector_node.h"
#include"behavior_status.h"

SelectorNode::SelectorNode(std::vector<std::shared_ptr<NodeBase>> nodes)
	:CompositeNode(nodes)
{

}

SelectorNode::~SelectorNode()
{

}

BehaviorStatus SelectorNode::Update()
{
	// 優先度の高いnodeから実行していく
	// その中でsuccessの場合はbreakする
	while (current_node_ < nodes_.size())
	{
		status_ = nodes_[current_node_]->Update();
		
		switch (status_)
		{
			// 実行完了
		case BehaviorStatus::kComplete:
			// ノードを初期化する
			nodes_[current_node_]->Exit();
			current_node_ = 0;
			return BehaviorStatus::kComplete;
			break;

			// 実行中
		case BehaviorStatus::kRunning:
			// 実行中なので同じノードへ
			return BehaviorStatus::kRunning;
			break;

			// 実行失敗
		case BehaviorStatus::kFailure:
			// 失敗なら次のノードへ
			nodes_[current_node_]->Exit();
			current_node_++;
			nodes_[current_node_]->Entry();
			break;
		}
	}
	//すべて失敗で抜けるので失敗
	return BehaviorStatus::kFailure;
}