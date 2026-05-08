#pragma once

class BehaviorBase;
class ObjectBase;
enum class BehaviorStatus;

class ChasePlayer : public BehaviorBase
{
public:

	ChasePlayer(std::weak_ptr<ObjectBase> owner,
		std::string my_anim_name,VECTOR* target_player_pos,float chase_speed);

	~ChasePlayer() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Debug() override;

private:

	std::string my_anim_name_;

	VECTOR* target_player_pos_;		// ターゲットしているplayerのpos
	float chase_speed_;					// スピード
};
