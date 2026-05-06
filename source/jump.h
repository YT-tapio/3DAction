#pragma once

class BehaviorBase;
class AnimatorBase;
class RigidBody;
enum class BehaviorStatus;

class Jump : public BehaviorBase
{
public:

	Jump(std::weak_ptr<ObjectBase> owner,
		std::string my_anim_name,float timing,float speed);

	~Jump() override;

	void Init() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Draw() override;

	void Debug() override;

private:

	bool JumpCondition(std::shared_ptr<AnimatorBase> animator,std::shared_ptr<RigidBody> owner_rigid_body);	// 飛べる条件

	std::string my_anim_name_;	// 自分のアニメーションの名前
	
	bool played_;	// ジャンプしたか
	float speed_;							//上昇値
	float timing_;							// ジャンプするタイミング(あにめーしょんの)
};
