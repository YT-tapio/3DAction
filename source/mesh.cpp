#include"DxLib.h"
#include"mesh.h"

Mesh::Mesh(int handle)
	:handle_(handle)
{

}


Mesh::~Mesh()
{

}

void Mesh::Draw(const VECTOR& pos)
{

}

const int Mesh::GetHandle() const
{
	return handle_;
}