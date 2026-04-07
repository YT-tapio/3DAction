#include<memory>
#include"vector_assistant.h"
#include"player_input.h"
#include"input_interface.h"
#include"pc.h"
#include"pad.h"
#include"key_config.h"
#include"pad_config.h"
#include"input_creater.h"

PlayerInput::PlayerInput()
	:InputBase()
{
	// 自分が生成されるときにmangagerから操作割り当てをもらう
	inputs_ = InputCreater::GetInstance().Create();	// 新しく生成
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
			if (pad->GetPushingTimeButton(PadConfig::dash) > 0.1f) { return TRUE; }
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

const bool PlayerInput::IsPunch() const
{
	// 攻撃に対応されているボタンを見る
	// padはbボタン長押しで
	for (auto& input : inputs_)
	{
		auto pad = std::dynamic_pointer_cast<Pad>(input);
		float pushing_time = 0.f;
		if (pad != nullptr)
		{
			pushing_time = pad->GetPushingTimeButton(PadConfig::punch);
			if (pushing_time == 0.f) { return TRUE; }
		}
		else
		{
			auto pc = std::dynamic_pointer_cast<PC>(input);
			if (pc != nullptr)
			{
				pushing_time = pc->GetPushingTimeMouseButton(KeyConfig::punch);

				if (pushing_time == 0.f ) { return TRUE; }
			}
		}
	}
	return FALSE;
}

const bool PlayerInput::IsAvoid() const
{
	// 攻撃に対応されているボタンを見る
	// padはbボタン長押しで
	for (auto& input : inputs_)
	{
		auto pad = std::dynamic_pointer_cast<Pad>(input);
		float pushing_time = 0.f;
		if (pad != nullptr)
		{
			pushing_time = pad->GetPushingTimeButton(PadConfig::avoid);
			if (pushing_time == 0.f) { return TRUE; }
		}
		else
		{
			auto pc = std::dynamic_pointer_cast<PC>(input);
			if (pc != nullptr)
			{
				pushing_time = pc->GetPushingTimeMouseButton(KeyConfig::avoid);

				if (pushing_time == 0.f) 
				{ 
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

const bool PlayerInput::IsNormalSkill() const
{
	// 攻撃に対応されているボタンを見る
	// padはbボタン長押しで
	for (auto& input : inputs_)
	{
		auto pad = std::dynamic_pointer_cast<Pad>(input);
		float pushing_time = 0.f;
		if (pad != nullptr)
		{
			pushing_time = pad->GetPushingTimeButton(PadConfig::normal_skil);
			if (pushing_time == 0.f) { return TRUE; }
		}
		else
		{
			auto pc = std::dynamic_pointer_cast<PC>(input);
			if (pc != nullptr)
			{
				pushing_time = pc->GetPushingTimeMouseButton(KeyConfig::normal_skill);

				if (pushing_time == 0.f) { return TRUE; }
			}
		}
	}
	return FALSE;
}

const bool PlayerInput::IsStrongSkill() const
{
	// 攻撃に対応されているボタンを見る
	// padはbボタン長押しで
	for (auto& input : inputs_)
	{
		auto pad = std::dynamic_pointer_cast<Pad>(input);
		float pushing_time = 0.f;
		if (pad != nullptr)
		{
			pushing_time = pad->GetPushingTimeButton(PadConfig::strong_skil);
			if (pushing_time == 0.f) { return TRUE; }
		}
		else
		{
			auto pc = std::dynamic_pointer_cast<PC>(input);
			if (pc != nullptr)
			{
				pushing_time = pc->GetPushingTimeMouseButton(KeyConfig::strong_skill);

				if (pushing_time == 0.f) { return TRUE; }
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

const VECTOR PlayerInput::GetCameraDir() const
{
	VECTOR input_move_camera_dir = VectorAssistant::VGetZero();

	for (auto& input : inputs_)
	{
		auto pad = std::dynamic_pointer_cast<Pad>(input);
		if (pad != nullptr)
		{
			// パッドを優先的にしたいのでpadに入力がある際は優先的に
			VECTOR pad_move_dir = CameraMoveDirPad(pad);
			if (VSize(pad_move_dir) > 0)
			{
				input_move_camera_dir = pad_move_dir;
			}
		}
		else
		{
			//pcの入力
			auto pc = std::dynamic_pointer_cast<PC>(input);
			if (pc != nullptr)
			{
				input_move_camera_dir = CameraMoveDirPC(pc);
			}
		}
		
	}

	return input_move_camera_dir;
}

const VECTOR PlayerInput::GetCameraVelocity() const
{
	VECTOR input_move_camera_vel = VectorAssistant::VGetZero();

	for (auto& input : inputs_)
	{
		auto pad = std::dynamic_pointer_cast<Pad>(input);
		if (pad != nullptr)
		{
			// パッドを優先的にしたいのでpadに入力がある際は優先的に
			VECTOR pad_move_dir = CameraMoveVelPad(pad);
			if (VSize(pad_move_dir) > 0)
			{
				input_move_camera_vel = pad_move_dir;
			}
		}
		else
		{
			//pcの入力
			auto pc = std::dynamic_pointer_cast<PC>(input);
			if (pc != nullptr)
			{
				input_move_camera_vel = CameraMoveVelPC(pc);
			}
		}

	}

	return input_move_camera_vel;
}

const VECTOR PlayerInput::MoveDirPC(std::shared_ptr<PC> pc) const
{
	VECTOR move_dir = VectorAssistant::VGetZero();

	if (pc->GetPushingTimeKey(KeyConfig::move_front)		>= 0.f) { move_dir.y += 1.f; }
	if (pc->GetPushingTimeKey(KeyConfig::move_back)		>= 0.f) { move_dir.y -= 1.f; }
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

const VECTOR PlayerInput::CameraMoveDirPC(std::shared_ptr<PC> pc) const
{
	VECTOR camera_move_dir = VectorAssistant::VGetZero();

	// 情報を受け取る
	camera_move_dir = pc->GetMouseDir();

	return camera_move_dir;
}

const VECTOR PlayerInput::CameraMoveDirPad(std::shared_ptr<Pad> pad) const
{
	VECTOR camera_move_dir = VectorAssistant::VGetZero();

	camera_move_dir = pad->GetRightStickDir();
		
	return camera_move_dir;
}

const VECTOR PlayerInput::CameraMoveVelPC(std::shared_ptr<PC> pc) const
{
	VECTOR camera_move_dir = VectorAssistant::VGetZero();

	// 情報を受け取る
	camera_move_dir = pc->GetMouseVel();

	return camera_move_dir;
}

const VECTOR PlayerInput::CameraMoveVelPad(std::shared_ptr<Pad> pad) const
{
	VECTOR camera_move_dir = VectorAssistant::VGetZero();

	camera_move_dir = VScale(pad->GetRightStickDir(), 20.f);
	camera_move_dir.x = -camera_move_dir.x;

	return camera_move_dir;
}