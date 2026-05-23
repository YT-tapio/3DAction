#pragma once
#include"DxLib.h"
#include"physics_interface.h"

class RigidBody;
class ObjectBase;
class ColliderBase;

class CheckMyArea : public IPhysicsEventReceiver
{
public:

	CheckMyArea(std::shared_ptr<ColliderBase> coll,VECTOR* pos);

	virtual ~CheckMyArea() override;

	void Init();

	virtual void Debug();

	/// <summary>
	/// ‰½‚©‚ÉÚG‚µ‚½‚Ìˆ—
	/// </summary>
	/// <param name="object"></param>
	virtual void OnHit(std::shared_ptr<IPhysicsEventReceiver> object) override;

	virtual void UnHit(std::shared_ptr<IPhysicsEventReceiver> object) override;

	std::vector<std::weak_ptr<ObjectBase>> GetMyAreaObject();

	std::shared_ptr<RigidBody> GetRigidBody() override;

	const VECTOR GetPos() const;

protected:

	std::shared_ptr<RigidBody> rigid_body_;
	std::vector<std::weak_ptr<ObjectBase>> my_area_objects_;

private:



};