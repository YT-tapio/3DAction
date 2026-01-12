#include<iostream>
#include"DxLib.h"

#include"set_object.h"


SetObject::SetObject(const int& handle, VECTOR* pos, VECTOR* rot, VECTOR* scale)
	:handle_(handle)
	, pos_(pos)
	, rot_(rot)
	, scale_(scale)
{

}

SetObject::~SetObject()
{

}

void SetObject::Update()
{
	// matrix‚É•ÏŠ·
	MATRIX scale_mat = MGetScale(*scale_);
	MATRIX rot_mat = MMult(MMult(MGetRotX(rot_->x), MGetRotY(rot_->y)), MGetRotZ(rot_->z));
	MATRIX mat = MMult(MMult(scale_mat, rot_mat), MGetTranslate(*pos_));
	MV1SetMatrix(handle_, mat);
}