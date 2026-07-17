#pragma once

class DamageUI;

class DamageUIGroup
{
public:

	static DamageUIGroup& GetInstance()
	{
		static DamageUIGroup instance;
		return instance;
	}

	DamageUIGroup(const DamageUIGroup&) = delete;
	DamageUIGroup& operator = (const DamageUIGroup&) = delete;

	void Awake();

	void Init();

	void Update();

	const void Draw() const;

	void SpawnPlayerDamageUI(const VECTOR& pos,const float& damage);

	void SpawnEnemyDamageUI(const VECTOR& pos, const float& damage);

	void End();

private:

	DamageUIGroup();

private:

	const int kMaxDamageUI = 10;

	std::vector<std::shared_ptr<DamageUI>> player_damage_uis_;	// player‚ªƒ_ƒ[ƒW‚ğó‚¯‚½Û‚É•`‰æ‚·‚é
	std::vector<std::shared_ptr<DamageUI>> enemy_damage_uis_;	// enemy‚ªUŒ‚‚ğó‚¯‚½Û‚É•`‰æ‚·‚é

};