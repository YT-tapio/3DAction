#pragma once

class ColliderBase;
class IPhysicsEventReceiver;
class ColliderGroup;
class VariableTimer;


class RigidBody
{
public:

	RigidBody(std::shared_ptr<ColliderBase> coll, VECTOR* pos, bool gravity, bool kinematic, float mass, float friction);

	~RigidBody();

	void Init(std::weak_ptr<IPhysicsEventReceiver> object);

	void ResetVelocity();

	void SetVelocity(const VECTOR& vel);

	void SetTargetVelocity(const VECTOR& vel);

	void SetTag(std::string tag);

	/// <summary>
	/// アクティブ状態(存在している状態)
	/// </summary>
	void Active();

	/// <summary>
	/// 非アクティブ
	/// </summary>
	void NotActive();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// velocityの更新
	/// </summary>
	/// <param name="vel"></param>
	void UpdateVelocity(const VECTOR& vel);

	// 重力処理
	void AddForce();

	void SetPos();

	/// <summary>
	/// 上昇値の設定(fall_speedをプラスにする)
	/// </summary>
	/// <param name="speed"></param>
	void SetUpSpeed(float speed);
	
	void CanMove();

	void SetStop(const float& time = -1.f);

	void OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object);

	void OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object);

	void OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object);

	void OnHit(std::shared_ptr<IPhysicsEventReceiver> object);

	void UnHit(std::shared_ptr<IPhysicsEventReceiver> object);

	void OnGround(std::shared_ptr<IPhysicsEventReceiver> object);

	void UnGround();

	const void Debug() const;

	const float GetMaxSpeed() const;

	const float GetFriction() const;

	const float GetFallSpeed() const;

	const float GetOwnerDeltaTime() const;

	const VECTOR GetPosition()const;

	const VECTOR GetVelocity()const;

	const VECTOR GetTargetVelocity() const;

	const bool IsMove() const;

	const bool IsStop() const;

	const bool GetUseGravity() const;

	const bool GetIsKinematic() const;

	const bool GetOnGround() const;

	const bool GetIsLanding() const;

	/// <summary>
	/// 自分がobjectなのか
	/// </summary>
	/// <returns></returns>
	const bool IsObject() const;

	const bool CheckSameOwner(std::shared_ptr<IPhysicsEventReceiver> other_object) const;

	/// <summary>
	/// タグを返す
	/// </summary>
	/// <returns></returns>
	const std::string GetTag() const;

	std::shared_ptr<ColliderBase> GetCollider();

	std::shared_ptr<IPhysicsEventReceiver> GetIPhysicsObject();

	const bool GetIsActive() const;

private:

	const float kMaxSpeed = 3.f;

	VECTOR* pos_;
	VECTOR vel_;
	VECTOR dir_;

	VECTOR target_vel_;

	bool is_stop_;

	bool use_gravity_;		// 重力
	bool is_kinematic_;		// 摩擦や重力による変更を受けない(TRUE : 受けない,FALSE ： 受ける)
	bool on_ground_;		// 着地判定
	bool is_landing_;		// 着地した瞬間
	bool is_object_;		// 自分はobjectなのか
	bool is_active_;
	float mass_;			// 重さ
	float friction_;		// 摩擦(0～1の間)0に近づくほど摩擦が強くなる

	float fall_speed_;

	std::string tag_;		// タグ
	bool tag_first_change_;	// タグの最初のチェンジ
	std::shared_ptr<ColliderBase>	coll_;				// 自分の当たり判定
	std::weak_ptr<IPhysicsEventReceiver>				object_;	// インターフェースを継承したオブジェクト
	std::shared_ptr<VariableTimer> stop_timer_;	// どのくらい時間を止めるかのタイマー

};