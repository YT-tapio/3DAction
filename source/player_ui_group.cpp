#include<vector>
#include<memory>
#include<string>
#include<functional>
#include"player_ui_group.h"
#include"object_base.h"
#include"image_data.h"
#include"object_2D.h"
#include"hp_bar.h"
#include"hp_actual_value_ui.h"
#include"player_last_background_ui.h"

void PlayerUIGroup::Init()
{

}

void PlayerUIGroup::Update()
{
	if (hpbar_ui_ != nullptr) { hpbar_ui_->Update(); }
}

void PlayerUIGroup::Draw()
{
	if (last_background_ != nullptr) { last_background_->Draw(); }
	if(hpbar_ui_ != nullptr){ hpbar_ui_->Draw(); }
	if (hp_actual_ui_ != nullptr) { hp_actual_ui_->Draw(); }
}

void PlayerUIGroup::MakeHPUI(std::function<int()> get_base_hp, std::function<int()> get_current_hp)
{
	hpbar_ui_ = std::make_shared<HPBar>("data/csv/ui/player/hp_bar_datas.csv", get_base_hp, get_current_hp);
	hp_actual_ui_ = std::make_shared<HPActualValueUI>("data/csv/ui/player/hp_actual.csv", get_current_hp);
	last_background_ = std::make_shared<PlayerLastBackGroundUI>();
}

PlayerUIGroup::PlayerUIGroup()
{

}