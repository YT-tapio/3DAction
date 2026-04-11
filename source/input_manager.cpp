#include<memory>
#include<vector>
#include"DxLib.h"
#include"pc.h"
#include"pad.h"
#include"input_manager.h"
#include"input_creater.h"
#include"input_base.h"
#include"player_input.h"
#include"ai_input.h"



void InputManager::Init()
{

}

void InputManager::Update()
{

	if (CheckHitKey(KEY_INPUT_6))
	{
		auto input = std::dynamic_pointer_cast<PlayerInput>(player_input_);
		if (input == nullptr) { return; }
		ai_input_ = player_input_;
		player_input_ = std::make_shared<AIInput>();
	}

	if (CheckHitKey(KEY_INPUT_0))
	{
		auto input = std::dynamic_pointer_cast<PlayerInput>(ai_input_);
		if (input == nullptr) { return; }
		player_input_ = ai_input_;
		ai_input_ = std::make_shared<AIInput>();
	}

	player_input_->Update();
	ai_input_->Update();
	ai_input_2->Update();
	ai_input_3->Update();
}

const std::shared_ptr<const InputBase> InputManager::GetPlayerInput() const
{
	std::shared_ptr<const InputBase> input = player_input_;
	return input;
}

const std::shared_ptr<const InputBase> InputManager::GetAIInput() const
{
	std::shared_ptr<const InputBase> input = ai_input_;
	return input;
}

const std::shared_ptr<const InputBase> InputManager::GetAIInput2() const
{
	std::shared_ptr<const InputBase> input = ai_input_2;
	return input;
}

const std::shared_ptr<const InputBase> InputManager::GetAIInput3() const
{
	std::shared_ptr<const InputBase> input = ai_input_3;
	return input;
}

InputManager::InputManager()
{
	Awake();
}

void InputManager::Awake()
{
	player_input_ = std::make_shared<PlayerInput>();
	ai_input_ = std::make_shared<AIInput>();
	ai_input_2 = std::make_shared<AIInput>();
	ai_input_3 = std::make_shared<AIInput>();
}