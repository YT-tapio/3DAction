#pragma once

class ObjectBase;
class ColliderBase;
class IPhysicsEventReceiver;

class RigidBody
{
public:

	RigidBody(std::shared_ptr<ColliderBase> coll, std::shared_ptr<ColliderBase> foot_coll,VECTOR* pos, bool gravity, bool kinematic, float mass);

	~RigidBody();

	void Init(std::weak_ptr<IPhysicsEventReceiver> object);

	void Update(const VECTOR& vel);

	void SetPos();

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> object);

	const VECTOR GetPosition()const;

	const VECTOR GetVelocity()const;

	const VECTOR GetBeforeVelocity() const;

	const bool IsMove() const;

	const bool GetUseGravity() const;

	const bool GetIsKinematic() const;

	std::shared_ptr<ColliderBase> GetCollider();

	std::shared_ptr<ColliderBase> GetFootCollider();

	std::shared_ptr<IPhysicsEventReceiver> GetIPhysicsObject();

private:

	VECTOR* pos_;
	VECTOR vel_;
	VECTOR dir_;

	VECTOR before_vel_;		// 1つ前の移動量を保存

	bool use_gravity_;		// 重力
	bool is_kinematic_;		// 摩擦や重力による変更を受けない(TRUE : 受けない,FALSE ： 受ける)
	float mass_;			// 重さ

	std::shared_ptr<ColliderBase>	coll_;				// 自分の当たり判定
	std::shared_ptr<ColliderBase>	foot_coll_;			// 足元の着地判定
	std::weak_ptr<IPhysicsEventReceiver>				object_;	// インターフェースを継承したオブジェクト

};