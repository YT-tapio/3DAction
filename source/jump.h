#pragma once

class BehaviorBase;
class CharacterBase;
class CharacterBehavior;
class AnimatorBase;
class RigidBody;
enum class BehaviorStatus;

class Jump : public CharacterBehavior
{
public:

	Jump(std::weak_ptr<CharacterBase> owner,std::string my_anim_name,std::pair<float,float>timing,float speed);

	~Jump() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Draw() override;

	void Debug() override;

private:

	bool JumpCondition(std::shared_ptr<CharacterBase> owner);	// 飛べる条件

	std::string my_anim_name_;	// 自分のアニメーションの名前
	
	std::pair<float, float> timing_; // この間はジャンプするタイミング

	bool played_;							// ジャンプしたか
	float speed_;							//上昇値
};
