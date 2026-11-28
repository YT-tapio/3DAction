#pragma once

class BehaviorBase;
class ObjectBase;
class EnemyMovementSupporter;
enum class BehaviorStatus;

class ChasePlayer : public BehaviorBase
{
public:

	ChasePlayer(std::weak_ptr<ObjectBase> owner, std::weak_ptr<EnemyMovementSupporter> enemy_movement_supporter,
		std::string my_anim_name,VECTOR* target_player_pos,float chase_speed);

	~ChasePlayer() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Debug() override;

private:

	std::weak_ptr<EnemyMovementSupporter> enemy_movement_supporter_;
	
	std::string my_anim_name_;

	VECTOR* target_player_pos_;		// ターゲットしているplayerのpos
	
	float chase_speed_;					// スピード

};
