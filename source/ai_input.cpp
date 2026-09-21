#include<memory>
#include<string>
#include"vector_assistant.h"
#include"ai_input.h"
#include"player.h"

AIInput::AIInput()
	:InputBase()
{

}

AIInput::~AIInput()
{

}

void AIInput::Init()
{

}

void AIInput::Update()
{

}

const bool AIInput::IsDash() const
{
	if (is_stop_) { return FALSE; }
	return TRUE;
}

const bool AIInput::IsPunch() const
{
	if (is_stop_) { return FALSE; }
	return TRUE;
}

const bool AIInput::IsAvoid() const
{
	if (is_stop_) { return FALSE; }
	return TRUE;
}

const bool AIInput::IsJump() const
{
	if (is_stop_) { return FALSE; }
	return TRUE;
}

const bool AIInput::IsNormalSkill() const
{
	if (is_stop_) { return FALSE; }
	return FALSE;
}

const bool AIInput::IsStrongSkill() const
{
	if (is_stop_) { return FALSE; }
	return FALSE;
}

const VECTOR AIInput::GetMoveDir() const
{

	VECTOR dir = VectorAssistant::VGetZero();
	if (is_stop_) { return dir; }
	dir.x = 1.f;
	dir = VNorm(dir);

	return dir;
}

const VECTOR AIInput::GetCameraDir() const
{
	VECTOR dir = VectorAssistant::VGetZero();
	return dir;
}