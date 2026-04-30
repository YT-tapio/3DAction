#pragma once

enum class BehaviorStatus;

class AttackBase;
class ObjectBase;
class IPhysicsEventReceiver;

class DoublePunch : public AttackBase
{
public:

	DoublePunch(std::weak_ptr<ObjectBase> owner, std::string my_anim_name,
		float min_coll_ratio, float max_coll_ratio, VECTOR* pos,float vertical, float radius);

	~DoublePunch() override;

	void Init() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Draw() override;

	void Debug()override;

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> object) override;

private:

	/// <summary>
	/// 当たり判定をactiveにするかどうか
	/// </summary>
	/// <returns></returns>
	const bool CheckCollActive() const;

	// パンチ
	std::string my_anim_name_;	// アニメーションの名前

	VECTOR* pos_;
};
