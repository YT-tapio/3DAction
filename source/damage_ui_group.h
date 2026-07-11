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

	void Spawn(const VECTOR& pos,const float& damage);

	void End();

private:

	DamageUIGroup();

private:

	const int kMaxDamageUI = 15;

	std::vector<std::shared_ptr<DamageUI>> damage_uis_;


};