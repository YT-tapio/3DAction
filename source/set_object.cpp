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
	VECTOR rot = *rot_;
	MATRIX rot_mat = MMult(MMult(MGetRotX(rot.x), MGetRotY(rot.y)), MGetRotZ(rot.z));
	MATRIX mat = MMult(MMult(scale_mat, rot_mat), MGetTranslate(*pos_));

	MV1SetupCollInfo(handle_);
	MV1SetMatrix(handle_, mat);
	MV1RefreshCollInfo(handle_);

}