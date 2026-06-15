#include<vector>
#include<memory>
#include<string>
#include<functional>
#include"player_ui_group.h"
#include"object_base.h"
#include"image_data.h"
#include"object_2D.h"
#include"hp_bar.h"
#include"string_ui.h"
#include"hp_actual_value_ui.h"
#include"player_last_background_ui.h"
#include"player_icon_ui.h"
#include"character_name_ui.h"
#include"animator_2d.h"
#include"draw_2D.h"

void PlayerUIGroup::Init()
{

}

void PlayerUIGroup::Update()
{
	if (hpbar_ != nullptr) { hpbar_->Update(); }
	if (icon_ != nullptr) { icon_->Update(); }
}

void PlayerUIGroup::Draw()
{
	if (last_background_ != nullptr) { last_background_->Draw(); }
	if(hpbar_ != nullptr){ hpbar_->Draw(); }
	if (hp_actual_ != nullptr) { hp_actual_->Draw(); }
	if (icon_ != nullptr) { icon_->Draw(); }
	if (player_name_ != nullptr) { player_name_->Draw(); }
}

void PlayerUIGroup::MakeHPUI(std::function<int()> get_base_hp, std::function<int()> get_current_hp,const std::string& name)
{
	hpbar_ = std::make_shared<HPBar>("data/csv/ui/player/hp_bar_datas.csv", get_base_hp, get_current_hp);
	hp_actual_ = std::make_shared<HPActualValueUI>("data/csv/ui/player/hp_actual.csv", get_current_hp);
	last_background_ = std::make_shared<PlayerLastBackGroundUI>();
	icon_ = std::make_shared<PlayerIconUI>(name);
	player_name_ = std::make_shared<CharacterNameUI>("data/csv/ui/player/" + name + "/" + name + "_name_data.csv", name);
}

void PlayerUIGroup::End()
{

}

PlayerUIGroup::PlayerUIGroup()
{

}