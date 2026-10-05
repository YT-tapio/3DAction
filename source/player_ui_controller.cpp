#include<string>
#include<functional>
#include<memory>
#include<unordered_map>
#include"DxLib.h"
#include"player_ui_controller.h"
#include"player_ui_group.h"

PlayerUIController::PlayerUIController()
{

}

PlayerUIController::~PlayerUIController()
{

}

void PlayerUIController::MakeUI(std::function<int()> get_base_hp, std::function<int()> get_current_hp, const std::string& name,const bool& is_main)
{
	const int kPlayerUIGroupsSize = player_ui_groups_.size();
	const VECTOR kOffsetPos = VScale(kOffset, kPlayerUIGroupsSize);
	// uiÇÃê∂ê¨
	player_ui_groups_[name] = std::make_shared<PlayerUIGroup>(kOffsetPos,is_main);
	player_ui_groups_[name]->MakeUI(get_base_hp, get_current_hp, "attacker");
}

void PlayerUIController::MakeStaminaUI(std::function<float()> get_base_stamina, std::function<float()> get_current_stamina,
	std::function<bool()> can_use_stamina, std::function<float()> get_avoid_use_stamina_value, const std::string& name)
{
	auto player_ui_group = player_ui_groups_.find(name);
	if (player_ui_group == player_ui_groups_.end()) { return; }
	if (player_ui_group->second == nullptr) { return; }
	player_ui_group->second->MakeStaminaUI(get_base_stamina, get_current_stamina, can_use_stamina, get_avoid_use_stamina_value);
}

void PlayerUIController::MakeNormalSkillUI(int skill_id, std::function<bool()> can_use, std::function<float()> cool_time_ratio, const std::string& name)
{

}

void PlayerUIController::MakeStrongSkillUI(int skill_id, std::function<bool()> can_use, std::function<float()> cool_time_ratio, const std::string& name)
{

}

void PlayerUIController::SpawnStatModifire(std::function<bool()> end_condition, StatType stat_type, ModifireOperation operation,const std::string& name)
{
	
}

void PlayerUIController::Init()
{
	for (auto player_ui_group : player_ui_groups_)
	{
		player_ui_group.second->Init();
	}
}

void PlayerUIController::Update()
{
	for (auto player_ui_group : player_ui_groups_)
	{
		player_ui_group.second->Update();
	}
}

void PlayerUIController::Draw()
{
	for (auto player_ui_group : player_ui_groups_)
	{
		player_ui_group.second->Draw();
	}
}

void PlayerUIController::ChangeIsMian(const bool& is_main, const std::string& name)
{
	auto player_ui_group = player_ui_groups_.find(name);
	if (player_ui_group == player_ui_groups_.end()) { return; }
	if (player_ui_group->second == nullptr) { return; }
	player_ui_group->second->SetIsMain(is_main);
}