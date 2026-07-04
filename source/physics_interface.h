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
	/// ‰½‚©‚ÉÚG‚µ‚½‚Ìˆ—
	/// </summary>
	/// <param name="object"></param>
	virtual void OnHit(std::shared_ptr<IPhysicsEventReceiver> object);

	/// <summary>
	/// hit‚µ‚Ä‚¢‚È‚¢‚Æ‚«
	/// </summary>
	/// <param name="object"></param>
	virtual void UnHit(std::shared_ptr<IPhysicsEventReceiver> object);

	/// <summary>
	/// “–‚½‚Á‚Ä‚¢‚é
	/// </summary>
	virtual void OnGround(std::shared_ptr<IPhysicsEventReceiver> object);

	/// <summary>
	/// “–‚½‚Á‚Ä‚¢‚È‚¢
	/// </summary>
	virtual void UnGround();

	/// <summary>
	/// rigid_body‚ğó‚¯æ‚é
	/// </summary>
	/// <returns></returns>
	virtual std::shared_ptr<RigidBody> GetRigidBody();

	/// <summary>
	/// ƒvƒŒƒCƒ„[‚Ìdelta_time‚ğæ“¾‚·‚é
	/// </summary>
	virtual const float GetDeltaTime() const;
};