#include<iostream>
#include"DxLib.h"
#include"object_3D.h"

Object3D::Object3D(const char* kPath, const VECTOR& pos, const VECTOR& rot, const VECTOR& scale)
	:ObjectBase(pos, rot)
{
	handle_ = MV1LoadModel(kPath);

	if (handle_ == -1)
	{
		printfDx("ì«Ç›çûÇ›é∏îs\n");
	}

	scale_ = scale;

	Setting();
}

Object3D::~Object3D()
{
	MV1DeleteModel(handle_);
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

void Object3D::Setting()
{
	auto pos_mat		= MGetTranslate(pos_);
	auto rot_mat		= MGetRotY(rot_.y);
	auto scale_mat	= MGetScale(scale_);

	mat_ = MMult(MMult(rot_mat, scale_mat), pos_mat);
	MV1SetMatrix(handle_, mat_);
}