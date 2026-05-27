#include<iostream>
#include<memory>
#include<string>
#include"DxLib.h"
#include"physics_interface.h"
#include"rigid_body.h"

void IPhysicsEventReceiver::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void IPhysicsEventReceiver::OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void IPhysicsEventReceiver::OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void IPhysicsEventReceiver::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void IPhysicsEventReceiver::UnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void IPhysicsEventReceiver::OnGround(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void IPhysicsEventReceiver::UnGround()
{

}

std::shared_ptr<RigidBody> IPhysicsEventReceiver::GetRigidBody()
{
	return nullptr;
}