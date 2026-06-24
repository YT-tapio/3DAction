#include<memory>
#include<functional>
#include<string>
#include"DxLib.h"
#include"enemy_ui_group.h"
#include"hp_bar.h"
#include"string_ui.h"
#include"character_name_ui.h"

void EnemyUIGroup::Init()
{

}

void EnemyUIGroup::Update()
{
	if (hp_bar_ != nullptr) { hp_bar_->Update(); }
}

void EnemyUIGroup::Draw()
{
	if (hp_bar_ != nullptr) { hp_bar_->Draw(); }
	if (name_ != nullptr) { name_->Draw(); }
}

void EnemyUIGroup::MakeStatusUI(std::function<int()> get_base_hp, std::function<int()> get_current_hp, std::string name)
{
	hp_bar_ = std::make_shared<HPBar>("data/csv/ui/enemy/hp_bar_datas.csv", get_base_hp, get_current_hp);
	name_ = std::make_shared<CharacterNameUI>("data/csv/ui/enemy/" + name + "/name_data.csv",name);
}

EnemyUIGroup::EnemyUIGroup()
{

}