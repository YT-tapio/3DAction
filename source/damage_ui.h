#pragma once

class ConditionTimer;

class DamageUI
{
public:

	DamageUI(int font_handle_);

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

	// ~‚Ü‚Á‚Ä‚¢‚éŠÔ
	std::shared_ptr<ConditionTimer> stop_timer_;

	VECTOR spawn_pos_;
	VECTOR pos_;

	int font_handle_;

	float default_up_speed_;	// ‰Šú‚Ìã¸—Ê
	float current_up_speed_;
	float damage_;
	float alpha_value_; // 0`255

	bool is_jump_;
	bool is_active_;

};