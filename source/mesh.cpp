#include"DxLib.h"
#include"mesh.h"
#include"collider_name.h"
#include"contact.h"
#include"vector_assistant.h"

Mesh::Mesh(int handle)
	: ColliderBase(ColliderName::kMesh)
	, handle_(handle)
{

}


Mesh::~Mesh()
{

}

bool Mesh::CheckCollision(const VECTOR& my_pos, const VECTOR& vel,const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll,Contact& contact)
{
	bool is_hit = FALSE;

	return is_hit;
}

VECTOR Mesh::FixPos(const VECTOR& my_pos, const VECTOR& vel, const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll, Contact& contact)
{
	return VectorAssistant::VGetZero();
}

void Mesh::Draw(const VECTOR& pos)
{

}

const int Mesh::GetHandle() const
{
	return handle_;
}