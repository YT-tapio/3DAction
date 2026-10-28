#pragma once
#include<iostream>

class RigidBody;

class IPhysicsEventReceiver : public std::enable_shared_from_this<IPhysicsEventReceiver>
{
public:
	virtual ~IPhysicsEventReceiver() = default;
	
	virtual void OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object);

	virtual void OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object);

	virtual void OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object);

	/// <summary>
	/// 何かに接触した時の処理
	/// </summary>
	/// <param name="object"></param>
	virtual void OnHit(std::shared_ptr<IPhysicsEventReceiver> object);

	/// <summary>
	/// hitしていないとき
	/// </summary>
	/// <param name="object"></param>
	virtual void UnHit(std::shared_ptr<IPhysicsEventReceiver> object);

	/// <summary>
	/// 当たっている
	/// </summary>
	virtual void OnGround(std::shared_ptr<IPhysicsEventReceiver> object);

	/// <summary>
	/// 当たっていない
	/// </summary>
	virtual void UnGround();

	/// <summary>
	/// rigid_bodyを受け取る
	/// </summary>
	/// <returns></returns>
	virtual std::shared_ptr<RigidBody> GetRigidBody();

	/// <summary>
	/// オブジェクトのdelta_timeを取得する
	/// </summary>
	virtual const float GetDeltaTime() const;
};