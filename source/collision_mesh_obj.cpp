#include<memory>
#include<string>
#include"object_3D.h"
#include"physics_interface.h"
#include"collision_mesh_obj.h"
#include"vector_assistant.h"
#include"object_setter.h"
#include"rigid_body.h"
#include"physics.h"
#include"mesh.h"
#include"color.h"

CollisionMeshObject::CollisionMeshObject()
	: Object3D("collision")
{
	std::string path = "data/model/collision/test_CollisionField.mv1";
	handle_ = MV1LoadModel(path.c_str());
	if (handle_ == -1) { printfDx("ÉÇÉfÉãì«Ç›çûÇ›é∏îs\n"); }
	pos_ = VGet(0.f, 0.f, 30.f);
	scale_ = VectorAssistant::VGetSame(0.01f);

	ObjectSetter::GetInstance().AddResource(handle_, &pos_, &rot_, &scale_);
	rigid_body_ = std::make_shared<RigidBody>(std::make_shared<Mesh>(handle_), &pos_, FALSE, TRUE, 1.f, 1.f);
}

CollisionMeshObject::~CollisionMeshObject()
{

}

void CollisionMeshObject::Init()
{
	// rigidbodyÇìoò^
	rigid_body_->Init(weak_from_this());
	Physics::GetInstance().AddBody(rigid_body_);
}

void CollisionMeshObject::Debug()
{
	// Ç±Ç±Ç≈ìñÇΩÇËîªíËÇÃï`âÊ
	// MV1DrawModel(handle_);
	//DrawSphere3D(pos_, 1.f, 20, Color::kWhite, Color::kWhite, TRUE);
}

std::shared_ptr<RigidBody> CollisionMeshObject::GetRigidBody()
{
	return rigid_body_;
}
