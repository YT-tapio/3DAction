#include<iostream>
#include<memory>
#include"DxLib.h"
#include"rigid_body.h"
#include"object_base.h"
#include"collider_base.h"
#include"vector_assistant.h"


RigidBody::RigidBody(std::shared_ptr<ColliderBase> coll, VECTOR* pos)
{
	pos_ = pos;
	vel_ = VectorAssistant::VGetZero();
	dir_ = VectorAssistant::VGetZero();
	coll_ = coll;
}

RigidBody::~RigidBody()
{

}

void RigidBody::Init(void (*op)(std::shared_ptr<ObjectBase>), std::weak_ptr<ObjectBase> object)
{
	hit = op;
	object_ = object;
}

void RigidBody::Update(const VECTOR& vel, const VECTOR& dir)
{
	vel_ = vel;
	dir_ = dir;
}

