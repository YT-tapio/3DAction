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
	player_input_->Update();
	ai_input_->Update();
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

InputManager::InputManager()
{
	Awake();
}

void InputManager::Awake()
{
	player_input_ = std::make_shared<PlayerInput>();
	ai_input_ = std::make_shared<AIInput>();
}