#pragma once
#include"popup_ui_group_interface.h"

class DamageUI;
class NumberPopupUI;

class PopupUIGroup : public IPopupUIGroup
{
public:

	PopupUIGroup();
	
	~PopupUIGroup();

	void Awake();

	void Init();

	void Update();

	const void Draw() const;

	void SpawnPlayerDamageUI(const VECTOR& pos,const float& damage, const bool is_critical) override;

	void SpawnEnemyDamageUI(const VECTOR& pos, const float& damage, const bool is_critical) override;

private:

	const int kMaxDamageUI = 10;

	std::vector<std::shared_ptr<NumberPopupUI>> player_damage_uis_;	// player‚ªƒ_ƒ[ƒW‚ğó‚¯‚½Û‚É•`‰æ‚·‚é
	std::vector<std::shared_ptr<NumberPopupUI>> enemy_damage_uis_;	// enemy‚ªUŒ‚‚ğó‚¯‚½Û‚É•`‰æ‚·‚é

};