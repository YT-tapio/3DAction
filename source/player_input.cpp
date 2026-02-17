#include<memory>
#include"vector_assistant.h"
#include"player_input.h"
#include"input_interface.h"
#include"pc.h"
#include"pad.h"
#include"key_config.h"

PlayerInput::PlayerInput()
	:InputBase()
{
	
}

PlayerInput::~PlayerInput()
{

}

void PlayerInput::Init()
{
	
}

void PlayerInput::Update()
{
	for (auto& input : inputs_)
	{
		input->Update();
	}
}

VECTOR PlayerInput::GetMoveDir()
{
	VECTOR move_dir = VectorAssistant::VGetZero();

	// 入力値を受け取る
	for (auto& input : inputs_)
	{
		auto pad = std::dynamic_pointer_cast<Pad>(input);
		
		if (pad != nullptr)
		{
			// パッドを優先的にしたいのでpadに入力がある際は優先的に
			VECTOR pad_move_dir = MoveDirPad(pad);
		}
		else
		{
			//pcの入力
			auto pc = std::dynamic_pointer_cast<PC>(input);
			move_dir = MoveDirPC(pc);
		}

	}

	return move_dir;
}


VECTOR PlayerInput::MoveDirPC(std::shared_ptr<PC> pc)
{
	VECTOR dir = VectorAssistant::VGetZero();

	if (pc->GetPushingTimeKey(KeyConfig::move_front)	>= 0.f) { dir.z += 1; }
	if (pc->GetPushingTimeKey(KeyConfig::move_back)		>= 0.f) { dir.z -= 1; }
	if (pc->GetPushingTimeKey(KeyConfig::move_left)		>= 0.f) { dir.x -= 1; }
	if (pc->GetPushingTimeKey(KeyConfig::move_right)	>= 0.f) { dir.x += 1; }

	return dir;
}

VECTOR PlayerInput::MoveDirPad(std::shared_ptr<Pad> pad)
{
	VECTOR move_dir = VectorAssistant::VGetZero();

	//move_dir = pad->GetLeftStickDir();

	return move_dir;
}