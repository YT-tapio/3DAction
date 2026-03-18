#pragma once

class ColliderBase;
class IPhysicsEventReceiver;
class ColliderGroup;

class RigidBody
{
public:

	RigidBody(std::shared_ptr<ColliderBase> coll, VECTOR* pos, bool gravity, bool kinematic, float mass);

	~RigidBody();

	void Init(std::weak_ptr<IPhysicsEventReceiver> object);

	void SetVelocity(const VECTOR& vel);

	void SetTargetVelocity(const VECTOR& vel);

	/// <summary>
	/// アクティブ状態(存在している状態)
	/// </summary>
	void Active();

	/// <summary>
	/// 非アクティブ
	/// </summary>
	void NotActive();

	void Update(const VECTOR& vel);

	//重力処理
	void AddForce();

	void ResetGravity();

	void SetPos();

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> object);

	void UnHit(std::shared_ptr<IPhysicsEventReceiver> object);

	const void Debug() const;

	const float GetMaxSpeed() const;

	const VECTOR GetPosition()const;

	const VECTOR GetVelocity()const;

	const VECTOR GetBeforeVelocity() const;

	const VECTOR GetTargetVelocity() const;

	const bool IsMove() const;

	const bool GetUseGravity() const;

	const bool GetIsKinematic() const;

	std::shared_ptr<ColliderBase> GetCollider();

	std::shared_ptr<IPhysicsEventReceiver> GetIPhysicsObject();

	const bool GetIsActive() const;

private:

	const float kMaxSpeed = 3.f;

	VECTOR* pos_;
	VECTOR vel_;
	VECTOR dir_;

	VECTOR before_vel_;		// 1つ前の移動量を保存
	VECTOR target_vel_;


	bool use_gravity_;		// 重力
	bool is_kinematic_;		// 摩擦や重力による変更を受けない(TRUE : 受けない,FALSE ： 受ける)
	bool on_grounded_;		// 着地判定
	float mass_;			// 重さ

	std::shared_ptr<ColliderBase>	coll_;				// 自分の当たり判定
	std::weak_ptr<IPhysicsEventReceiver>				object_;	// インターフェースを継承したオブジェクト

	bool is_active_;

};