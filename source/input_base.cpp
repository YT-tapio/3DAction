#include<vector>
#include<memory>
#include"DxLib.h"
#include"vector_assistant.h"
#include"input_base.h"
#include"input_interface.h"


InputBase::InputBase()
	: is_stop_(FALSE)
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

void InputBase::Stop()
{
	is_stop_ = TRUE;
}

void InputBase::Start()
{
	is_stop_ = FALSE;
}

const bool InputBase::IsPush(ConfigName name) const
{
	return FALSE;
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

const bool InputBase::IsNormalSkill() const
{
	return FALSE;
}

const bool InputBase::IsStrongSkill() const
{
	return FALSE;
}

const bool InputBase::IsLockOnEnemy() const
{
	return FALSE;
}

const bool InputBase::GoNextScene() const
{
	return FALSE;
}

const bool InputBase::GoResult() const
{
	return FALSE;
}

const bool InputBase::Retry() const
{
	return FALSE;
}

const bool InputBase::GameToTitle() const
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