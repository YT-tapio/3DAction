#include<vector>
#include<memory>
#include"DxLib.h"
#include"vector_assistant.h"
#include"input_base.h"
#include"input_interface.h"


InputBase::InputBase()
{
	
}

InputBase::~InputBase()
{

}

void InputBase::Init()
{
	
}

void InputBase::Update()
{

}

const bool InputBase::IsDash() const
{
	//base‚Ì‚Ü‚Ü‚¾‚Æfalse
	return FALSE;
}

const bool InputBase::IsPunch() const
{
	return FALSE;
}

const bool InputBase::IsAvoid() const
{
	return FALSE;
}

const VECTOR InputBase::GetMoveDir() const
{
	return VectorAssistant::VGetZero();
}

const VECTOR InputBase::GetCameraDir() const
{
	return VectorAssistant::VGetZero();
}

const VECTOR InputBase::GetCameraVelocity() const
{
	return VectorAssistant::VGetZero();
}