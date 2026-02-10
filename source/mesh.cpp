#include"DxLib.h"
#include"mesh.h"
#include"collider_name.h"
#include"contact.h"

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

void Mesh::FixPos(const VECTOR& my_pos, const VECTOR& vel, const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll, Contact& contact)
{

}

void Mesh::Draw(const VECTOR& pos)
{

}

const int Mesh::GetHandle() const
{
	return handle_;
}