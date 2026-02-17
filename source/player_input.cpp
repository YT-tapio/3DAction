#include<memory>
#include"vector_assistant.h"
#include"player_input.h"
#include"input_interface.h"
#include"pc.h"
#include"pad.h"
#include"key_config.h"
#include"pad_config.h"

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

const bool PlayerInput::IsDash() const
{
	// ダッシュに対応されているボタンを見る
	// padはbボタン長押しで
	for (auto& input : inputs_)
	{
		auto pad = std::dynamic_pointer_cast<Pad>(input);
		if (pad != nullptr)
		{
			if (pad->GetPushingTimeButton(PadConfig::jump) > 0.1f) { return TRUE; }
		}
		else
		{
			auto pc = std::dynamic_pointer_cast<PC>(input);
			if (pc != nullptr)
			{
				if (pc->GetPushingTimeKey(KeyConfig::dash) > 0.1f) { return TRUE; }
			}
		}
	}
	return FALSE;
}

const VECTOR PlayerInput::GetMoveDir() const
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
			if (VSize(pad_move_dir) > 0) 
			{ 
				move_dir = pad_move_dir;
			}
		}
		else
		{
			//pcの入力
			auto pc = std::dynamic_pointer_cast<PC>(input);
			if (pc != nullptr)
			{
				move_dir = MoveDirPC(pc);
			}
		}

	}

	return move_dir;
}

const VECTOR PlayerInput::MoveDirPC(std::shared_ptr<PC> pc) const
{
	VECTOR move_dir = VectorAssistant::VGetZero();

	if (pc->GetPushingTimeKey(KeyConfig::move_front)		>= 0.f) { move_dir.z += 1.f; }
	if (pc->GetPushingTimeKey(KeyConfig::move_back)		>= 0.f) { move_dir.z -= 1.f; }
	if (pc->GetPushingTimeKey(KeyConfig::move_left)		>= 0.f) { move_dir.x -= 1.f; }
	if (pc->GetPushingTimeKey(KeyConfig::move_right)		>= 0.f) { move_dir.x += 1.f; }
	if (VSize(move_dir) > 0){ move_dir = VNorm(move_dir); }	// 正規化

	return move_dir;
}

const VECTOR PlayerInput::MoveDirPad(std::shared_ptr<Pad> pad) const
{
	VECTOR move_dir = VectorAssistant::VGetZero();
	move_dir = pad->GetLeftStickDir();
	return move_dir;
}