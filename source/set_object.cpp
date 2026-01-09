#include<iostream>
#include"DxLib.h"

#include"set_object.h"


SetObject::SetObject(const int& handle,MATRIX* mat)
	:handle_(handle)
	,mat_(mat)
{

}

SetObject::~SetObject()
{

}

void SetObject::Update()
{
	MV1SetMatrix(handle_, *mat_);
}