#include<string>
#include"load.h"
#include<memory>
#include"scene_manager.h"

Load::Load(const std::string& next_scene)
	: SceneBase()
	, next_scene_(next_scene)
{

}

Load::~Load()
{

}

void Load::Update()
{
	SceneManager::GetInstance().LoadScene2(next_scene_);
}