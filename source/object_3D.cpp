#include<iostream>
#include<string>
#include"DxLib.h"
#include"object_3D.h"
#include"vector_assistant.h"

Object3D::Object3D(const char* id)
	:ObjectBase()
{
	//static int count = 0;
	const float kDefaultSize = 1.f;
	path_ = "";
	handle_ = -1;
	scale_ = VectorAssistant::VGetSame(kDefaultSize);
	//printfDx("Object3D destroyed: %d\n", count);
	//count++;
	//LoadFile();
}

Object3D::~Object3D()
{
	
	if (handle_ != -1)
	{
		MV1DeleteModel(handle_);
		handle_ = -1;
	}
	//static int count = 0;
	//printfDx("Object3D destroyed: %p,%d\n", this, count);
	//count++;
}

void Object3D::Init()
{

}

void Object3D::Update()
{
	Setting();
}

void Object3D::Draw()
{
	MV1DrawModel(handle_);
}

void Object3D::Debug()
{

}

void Object3D::LoadModel()
{
	auto path = path_.c_str();
	handle_ = MV1LoadModel(path);

	if (handle_ == -1) { printfDx("ÉÇÉfÉãÇÃì«Ç›çûÇ›é∏îs\n"); }
}

void Object3D::Setting()
{
	auto pos_mat		= MGetTranslate(pos_);
	auto rot_mat		= MGetRotY(rot_.y);
	auto scale_mat		= MGetScale(scale_);

	mat_ = MMult(MMult(rot_mat, scale_mat), pos_mat);
	MV1SetMatrix(handle_, mat_);
	// MV1SetScale(handle_, scale_);
	// MV1SetPosition(handle_, pos_);
}
/*
void Object3D::LoadFile()
{


}
*/
