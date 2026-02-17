#include<vector>
#include<memory>
#include"DxLib.h"
#include"vector_assistant.h"
#include"input_base.h"
#include"input_interface.h"
#include"input_state.h"
#include"input_creater.h"

InputBase::InputBase()
{
	// Ž©•ª‚ª¶¬‚³‚ê‚é‚Æ‚«‚Émangager‚©‚ç‘€ìŠ„‚è“–‚Ä‚ð‚à‚ç‚¤
	inputs_ = InputCreater::GetInstance().Create();	// V‚µ‚­¶¬
}

InputBase::~InputBase()
{

}

void InputBase::Init()
{
	
}

void InputBase::Update()
{
	for (auto& input : inputs_)
	{
		input->Update();
	}
}

const bool InputBase::IsDash() const
{
	//base‚Ì‚Ü‚Ü‚¾‚Æfalse
	return FALSE;
}

const VECTOR InputBase::GetMoveDir() const
{
	return VectorAssistant::VGetZero();
}