#include<vector>
#include<memory>
#include"composite_node.h"
#include"selector_node.h"
#include"node_status.h"

SelectorNode::SelectorNode(std::vector<std::shared_ptr<NodeBase>> nodes)
	:CompositeNode(nodes)
{

}

SelectorNode::~SelectorNode()
{

}

NodeStatus SelectorNode::Update()
{
	// 優先度の高いnodeから実行していく
	// その中でsuccessの場合はbreakする
	while (current_node_ < nodes_.size())
	{
		auto status = nodes_[current_node_]->Update();
		
		switch (status)
		{
			// 実行完了
		case NodeStatus::kSuccess:
			// ノードを初期化する
			current_node_ = 0;
			return NodeStatus::kSuccess;
			break;

			// 実行中
		case NodeStatus::kRunning:
			// 実行中なので同じノードへ
			return NodeStatus::kRunning;
			break;

			// 実行失敗
		case NodeStatus::kFailure:
			// 失敗なら次のノードへ
			current_node_++;
			break;
		}
	}
	//すべて失敗で抜けるので失敗
	return NodeStatus::kFailure;
}