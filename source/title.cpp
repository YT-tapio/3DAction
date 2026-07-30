#include<string>
#include<memory>
#include"DxLib.h"
#include"title.h"
#include"scene_manager.h"
#include"physics.h"
#include"input_manager.h"
#include"input_base.h"
Title::Title()
	: SceneBase()
{

}

Title::~Title()
{

}

void Title::Init()
{

}

void Title::Update()
{
	auto player_input = InputManager::GetInstance().GetMainPlayerInput();
	
	if (player_input != nullptr)
	{
		if (player_input->GoNextScene())
		{
			//Physics::GetInstance().End();
			SceneManager::GetInstance().LoadScene("game");
		}
	}
}

void Title::Draw()
{
	DrawString(100, 100, "Title", GetColor(255, 255, 255));
	DrawString(500, 700, "Aボタン、スペースを押してゲームスタート", GetColor(255, 255, 255));
}

const std::string Title::GetName() const
{
	return "title";
}
