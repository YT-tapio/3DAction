#pragma once

class ConditionTimer;
class Time;
class SubScreen;

class DamageUI
{
public:

	DamageUI(const std::string& file_path);

	~DamageUI();

	void Init();

	void Update();

	const void Draw() const;

	/// <summary>
	/// ¶¬
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="damage"></param>
	void Spawn(const VECTOR& pos, const float& damage);

	const bool GetIsActive() const;

private:

	VECTOR RandomSpawnPos(const VECTOR& pos);

	void DrawDamage();

	void LoadFile(const std::string& path);

private:

	// ~‚Ü‚Á‚Ä‚¢‚éŠÔ
	std::shared_ptr<ConditionTimer> stop_timer_;
	std::shared_ptr<Time> time_;
	std::shared_ptr<SubScreen> damage_screen_;	// ƒ_ƒ[ƒW•`‰æ‚Ìscreen

	VECTOR spawn_pos_;
	VECTOR pos_;

	int font_handle_;
	int font_color_;
	int edge_color_;

	float default_up_speed_;	// ‰Šú‚Ìã¸—Ê
	float current_up_speed_;
	float out_up_speed_;		// Á‚¦‚éÛ‚Ìã¸’l
	float damage_;
	float alpha_value_; // 0`255

	bool is_jump_;
	bool is_active_;

};