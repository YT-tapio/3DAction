#pragma once
#include<iostream>

class IPhysicsEventReceiver : public std::enable_shared_from_this<IPhysicsEventReceiver>
{
public:
	virtual ~IPhysicsEventReceiver() = default;
	
	/// <summary>
	/// ‰½‚©‚ÉÚG‚µ‚½‚Ìˆ—
	/// </summary>
	/// <param name="object"></param>
	virtual void OnHit(std::shared_ptr<IPhysicsEventReceiver> object);

	/// <summary>
	/// “–‚½‚Á‚Ä‚¢‚é
	/// </summary>
	virtual void OnGrounded();

	/// <summary>
	/// “–‚½‚Á‚Ä‚¢‚È‚¢
	/// </summary>
	virtual void OnUnGrounded();


};