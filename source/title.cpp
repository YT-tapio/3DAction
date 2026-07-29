#include<string>
#include<memory>
#include"DxLib.h"
#include"title.h"
#include"scene_manager.h"
#include"physics.h"
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
	if (CheckHitKey(KEY_INPUT_0))
	{
		//Physics::GetInstance().End();
		SceneManager::GetInstance().LoadScene("game");
	}
}

void Title::Draw()
{
	DrawString(100, 100, "Title", GetColor(255, 255, 255));
}

const std::string Title::GetName() const
{
	return "title";
}
