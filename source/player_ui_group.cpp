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
#include"ui_interface.h"
#include"stamina_ui.h"
#include"stat_modifire_ui_group.h"

PlayerUIGroup::PlayerUIGroup()
{

}

PlayerUIGroup::~PlayerUIGroup()
{

}

void PlayerUIGroup::Init()
{

}

void PlayerUIGroup::Update()
{
	if (hpbar_ != nullptr) { hpbar_->Update(); }
	if (icon_ != nullptr) { icon_->Update(); }
	if (stamina_ui_ != nullptr) { stamina_ui_->Update(); }
	if (stat_modifire_ui_group_ != nullptr) { 
		stat_modifire_ui_group_->Update(); }
}

void PlayerUIGroup::Draw()
{
	if (last_background_ != nullptr) { last_background_->Draw(); }
	if (hpbar_ != nullptr){ hpbar_->Draw(); }
	if (hp_actual_ != nullptr) { hp_actual_->Draw(); }
	if (icon_ != nullptr) { icon_->Draw(); }
	if (player_name_ != nullptr) { player_name_->Draw(); }
	if (stamina_ui_ != nullptr) { stamina_ui_->Draw(); }
	if (stat_modifire_ui_group_ != nullptr) { 
		stat_modifire_ui_group_->Draw(); }
}

void PlayerUIGroup::MakeUI(std::function<int()> get_base_hp, std::function<int()> get_current_hp,const std::string& name)
{
	hpbar_ = std::make_shared<HPBar>("data/csv/ui/player/hp_bar_datas.csv", get_base_hp, get_current_hp);
	hp_actual_ = std::make_shared<HPActualValueUI>("data/csv/ui/player/hp_actual.csv", get_current_hp);
	last_background_ = std::make_shared<PlayerLastBackGroundUI>();
	icon_ = std::make_shared<PlayerIconUI>(name);
	stat_modifire_ui_group_ = std::make_shared<StatModifireUIGroup>("data/csv/ui/stat_modifire/stat_modifire.csv");
	player_name_ = std::make_shared<CharacterNameUI>("data/csv/ui/player/" + name + "/" + name + "_name_data.csv", name);
}

void PlayerUIGroup::MakeStaminaUI(std::function<float()> get_base_stamina, std::function<float()> get_current_stamina,
	std::function<bool()> can_use_stamina, std::function<float()> get_avoid_use_stamina_value)
{
	stamina_ui_ = std::make_shared<StaminaUI>(get_base_stamina, get_current_stamina, can_use_stamina, get_avoid_use_stamina_value);
}

void PlayerUIGroup::SpawnStatModifire(std::function<bool()> end_condition, StatType stat_type, ModifireOperation operation)
{
	// 
	stat_modifire_ui_group_->Spawn(end_condition, stat_type, operation);
}