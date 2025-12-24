#pragma once

class ObjectBase;
class ColliderBase;
class IPhysicsEventReceiver;

class RigidBody
{
public:

	RigidBody(std::shared_ptr<ColliderBase> coll, std::shared_ptr<ColliderBase> foot_coll,VECTOR* pos,bool gravity,float mass);

	~RigidBody();

	void Init(std::weak_ptr<IPhysicsEventReceiver> object);

	void Update(const VECTOR& vel,const VECTOR& dir);

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> object);

	const VECTOR GetPosition()const;

	const VECTOR GetVelocity()const;

	const bool GetUseGravity() const;

	std::shared_ptr<ColliderBase> GetCollider();

	std::shared_ptr<ColliderBase> GetFootCollider();

	std::shared_ptr<IPhysicsEventReceiver> GetIPhysicsObject();

private:

	VECTOR* pos_;
	VECTOR vel_;
	VECTOR dir_;

	bool use_gravity_;
	float mass_;

	std::shared_ptr<ColliderBase>	coll_;				// 自分の当たり判定
	std::shared_ptr<ColliderBase> foot_coll_;	// 足元の着地判定
	std::weak_ptr<IPhysicsEventReceiver>				object_;	// インターフェースを継承したオブジェクト

};