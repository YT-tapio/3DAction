#include<vector>
#include<memory>
#include<string>
#include<functional>
#include"player_ui_group.h"
#include"object_base.h"
#include"image_data.h"
#include"object_2D.h"
#include"hp_bar.h"

void PlayerUIGroup::Init()
{

}

void PlayerUIGroup::Update()
{
	if (hp_ui_ != nullptr) { hp_ui_->Update(); }
}

void PlayerUIGroup::Draw()
{
	if(hp_ui_ != nullptr){ hp_ui_->Draw(); }
	
}

void PlayerUIGroup::MakeHPUI(std::function<int()> get_base_hp, std::function<int()> get_current_hp)
{
	hp_ui_ = std::make_shared<HPBar>("data/csv/ui/player/hp_datas.csv", get_base_hp, get_current_hp);
}

PlayerUIGroup::PlayerUIGroup()
{

}