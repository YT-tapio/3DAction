#include<memory>
#include<unordered_map>
#include"DxLib.h"
#include"pc.h"
#include"pad.h"
#include"input_manager.h"
#include"input_creater.h"
#include"input_base.h"
#include"player_input.h"
#include"ai_input.h"
#include"input_change_interface.h"

void InputManager::AddInput(std::weak_ptr<IInputChange> input)
{
	input_changers_[changers_num_] = input;
	changers_num_++;
}

void InputManager::Init()
{
	for (auto& input_id : input_id_mp_)
	{
		input_id.second->Update();
	}
}

void InputManager::Update()
{

	ChangeInput();

	for (auto& input_id : input_id_mp_)
	{
		input_id.second->Update();
	}
	
}

const std::shared_ptr<const InputBase> InputManager::GetPlayer1Input() const
{
	std::shared_ptr<const InputBase> input = input_id_mp_.find(kPlayer1Id)->second;
	return input;
}

const std::shared_ptr<const InputBase> InputManager::GetPlayer2Input() const
{
	std::shared_ptr<const InputBase> input = input_id_mp_.find(kPlayer2Id)->second;
	return input;
}

const std::shared_ptr<const InputBase> InputManager::GetPlayer3Input() const
{
	std::shared_ptr<const InputBase> input = input_id_mp_.find(kPlayer3Id)->second;
	return input;
}

const std::shared_ptr<const InputBase> InputManager::GetPlayer4Input() const
{
	std::shared_ptr<const InputBase> input = input_id_mp_.find(kPlayer4Id)->second;
	return input;
}

InputManager::InputManager()
{
	Awake();
}

void InputManager::Awake()
{

	input_id_mp_[kPlayer1Id] = std::make_shared<PlayerInput>();
	input_id_mp_[kPlayer2Id] = std::make_shared<AIInput>();
	input_id_mp_[kPlayer3Id] = std::make_shared<AIInput>();
	input_id_mp_[kPlayer4Id] = std::make_shared<AIInput>();
	/*
	player_input_ = std::make_shared<PlayerInput>();
	player2_input_ = std::make_shared<AIInput>();
	ai_input_2 = std::make_shared<AIInput>();
	ai_input_3 = std::make_shared<AIInput>();

	*/
	changers_num_ = 1;
}

void InputManager::ChangeInput()
{

	for (auto& input_id : input_id_mp_)
	{
		auto player_input = std::dynamic_pointer_cast<PlayerInput>(input_id.second);
		if (player_input == nullptr) { continue; }
		// •Ï‰»—Ê
		int num = input_id.first;
		int change_num = player_input->GetPlayerChangeNum(num);
		if (change_num == 0) { return; }	// •Ï‰»‚È‚µ‚È‚çI—¹
		int change_player_id = num + change_num;

		// ¡‚Í—v‘f‚Ê‚¯‚·‚é‰Â”\«‚ª‚ ‚é‚Ì‚Å‚»‚ê‚Ì‰ü‘P‚ğ‚µ‚Ü‚µ‚å‚¤

		if (change_player_id < kPlayer1Id)
		{
			change_player_id = changers_num_ - 1;
		}

		if (change_player_id > changers_num_ - 1)
		{
			change_player_id = kPlayer1Id;
		}

		auto changer_input = input_id_mp_.find(change_player_id)->second;			//æ‚Éplayer2‚Ìî•ñ‚ğ•Û‘¶
		input_id_mp_.find(change_player_id)->second = input_id_mp_.find(num)->second;// player1‚Ìî•ñ‚ğplayer2‚É‘ã“ü
		input_id_mp_.find(num)->second = changer_input;		// •Û‘¶‚µ‚Ä‚¢‚½‚à‚Ì‚ğ“ü‚ê‚é

		(input_changers_[num].lock())->InputChange(input_id_mp_.find(num)->second);
		(input_changers_[change_player_id].lock())->InputChange(input_id_mp_.find(change_player_id)->second);
		return;
	}
}