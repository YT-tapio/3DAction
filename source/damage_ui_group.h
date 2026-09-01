#pragma once
#include"damage_ui_group_interface.h"

class DamageUI;

class DamageUIGroup : public IDamageUIGroup
{
public:

	DamageUIGroup();
	
	~DamageUIGroup();

	void Awake();

	void Init();

	void Update();

	const void Draw() const;

	void SpawnPlayerDamageUI(const VECTOR& pos,const float& damage) override;

	void SpawnEnemyDamageUI(const VECTOR& pos, const float& damage) override;

private:

	const int kMaxDamageUI = 10;

	std::vector<std::shared_ptr<DamageUI>> player_damage_uis_;	// player‚ªƒ_ƒ[ƒW‚ğó‚¯‚½Û‚É•`‰æ‚·‚é
	std::vector<std::shared_ptr<DamageUI>> enemy_damage_uis_;	// enemy‚ªUŒ‚‚ğó‚¯‚½Û‚É•`‰æ‚·‚é

};