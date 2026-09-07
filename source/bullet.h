#pragma once
#include"object_3d.h"
#include"physics_interface.h"

class RigidBody;

class Bullet : public Object3D , public IPhysicsEventReceiver
{
public:

	Bullet();

	~Bullet() override;

	virtual void Init() override;

	virtual void Update() override;

	virtual void Draw() override;

	// ê∂ê¨
	void Shot(const VECTOR& pos,const VECTOR& dir);

	virtual void OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object) override;

	std::shared_ptr<RigidBody> GetRigidBody() override;

protected:

	std::shared_ptr<RigidBody> rigid_body_;

	VECTOR vel_;
	VECTOR dir_;

	int handle_;
	float speed_;

private:



};

