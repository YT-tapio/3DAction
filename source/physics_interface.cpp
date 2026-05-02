#include<iostream>
#include<memory>
#include"DxLib.h"
#include"physics_interface.h"
#include"rigid_body.h"

void IPhysicsEventReceiver::OnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void IPhysicsEventReceiver::UnHit(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void IPhysicsEventReceiver::OnGrounded(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void IPhysicsEventReceiver::OnUnGrounded(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

std::shared_ptr<RigidBody> IPhysicsEventReceiver::GetRigidBody()
{
	return nullptr;
}