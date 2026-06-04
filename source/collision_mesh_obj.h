#pragma once

class Object3D;
class IPhysicsEventReceiver;
class RigidBody;

// 当たり判定専用オブジェクト
class CollisionMeshObject : public Object3D,public IPhysicsEventReceiver
{
public:
	CollisionMeshObject();

	virtual ~CollisionMeshObject() override;

	virtual void Init() override;

	virtual void Debug() override;

	std::shared_ptr<RigidBody> GetRigidBody() override;

private:

	std::shared_ptr<RigidBody> rigid_body_;

};
