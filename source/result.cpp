#include<string>
#include<memory>
#include<unordered_map>
#include"result.h"
#include"DxLib.h"
#include"scene_manager.h"
#include"input_manager.h"
#include"input_base.h"

Result::Result()
{

}

Result::~Result()
{

}

void Result::Init()
{

}

void Result::Update()
{
	auto player_input = InputManager::GetInstance().GetMainPlayerInput();

	if (player_input != nullptr)
	{
		if (player_input->GoNextScene())
		{
			if (SceneManager::GetInstance().LoadScene("title")) { return; }
		}
	}
}

void Result::Draw()
{
	DrawString(100, 100, "result", GetColor(255, 255, 255));
	DrawString(500, 700, "Aボタン、スペースを押してタイトルへ", GetColor(255, 255, 255));
}

const std::string Result::GetName() const
{
	return "result";
}