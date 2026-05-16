#include<DxLib.h>
#include"transform.h"
#include"vector_assistant.h"

Transform::Transform()
	: pos_(VectorAssistant::VGetZero())
	, rot_(VGet(0.f,1.f,0.f))
	, scale_(VectorAssistant::VGetSame(1.f))
{

}

Transform::~Transform()
{

}