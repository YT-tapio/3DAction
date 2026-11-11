#pragma once
#include<vector>
#include"input_base.h"
#include"skill_type.h"

class PlayerGroup;
class BehaviorTree;
class NodeBase;

class AIInput : public InputBase
{
public:

	AIInput();

	~AIInput();

	void Init() override;

	void Update() override;

	void SetPlayerGroup(std::weak_ptr<PlayerGroup> player_group) override;

	void SetStickDir(const VECTOR& dir);

	void PushSkill(const SkillType& type);

	const bool CheckIsPlayer() const override;

	const bool IsDash() const override;

	const bool IsPunch() const override;

	const bool IsAvoid() const override;

	const bool IsJump() const override;
	
	const bool IsNormalSkill() const override;

	const bool IsStrongSkill() const override;

	const VECTOR GetMoveDir() const override;

	const VECTOR GetCameraDir() const override;

private:

	void MakeBehaviorTree();

	void ResetInfo();

	void LoadFile();

	std::shared_ptr<NodeBase> MakeExecuteSkillNode(const SkillType& type);

	std::shared_ptr<NodeBase> MakeChaseMainPlayerNode();

	VECTOR GetMainPlayerPos();

private:

	std::shared_ptr<BehaviorTree> behavior_tree_;
	std::weak_ptr<PlayerGroup> player_group_;

	VECTOR move_dir_;

	float dist_size_;
	
	// ëÄçÏèÛãµ
	bool is_push_normal_skill_;
	bool is_push_strong_skill_;
	bool is_push_dash_;
	bool is_push_avoid_;
	bool is_push_jump_;
};