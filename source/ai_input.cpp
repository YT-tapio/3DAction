#include<memory>
#include"vector_assistant.h"
#include"ai_input.h"


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

	return TRUE;
}

const bool AIInput::IsPunch() const
{

	return FALSE;
}

const bool AIInput::IsAvoid() const
{
	return FALSE;
}

const VECTOR AIInput::GetMoveDir() const
{
	VECTOR dir = VectorAssistant::VGetZero();
	//dir.x = 1.f;
	//dir = VNorm(dir);
	return dir;
}

const VECTOR AIInput::GetCameraDir() const
{
	VECTOR dir = VectorAssistant::VGetZero();
	return dir;
}