#include<string>
#include"DxLib.h"
#include"image_data.h"
#include"object_base.h"
#include"object_2d.h"

Object2D::Object2D(const ImageData data, const VECTOR& pos, float size_rate, float rot)
	: ObjectBase()
	, data_(data)
	, size_rate_(size_rate)
{
	handle_ = LoadGraph(data_.path.c_str());
	if (handle_ == -1) { printfDx("2DÅFì«Ç›çûÇ›ÉGÉâÅ[\n"); }
	pos_ = pos;
	rot_ = VGet(0.f, 0.f, rot);
}

Object2D::~Object2D()
{
	DeleteGraph(handle_);
}

void Object2D::Init()
{

}

void Object2D::Update()
{

}

void Object2D::Draw()
{
	DrawRotaGraph(static_cast<int>(pos_.x),
		static_cast<int>(pos_.y), size_rate_, rot_.z, handle_, TRUE, FALSE);
}

void Object2D::Debug()
{
	
}
