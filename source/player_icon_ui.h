#pragma once

class Animator2D;

class PlayerIconUI
{
public:

	PlayerIconUI(const std::string& name,std::function<int()> get_current_hp);

	~PlayerIconUI();

	void Update();

	const void Draw() const;

private:

	void LoadFile(const std::string& name);

private:

	const float kDefaultDarkPercent = 0.5f;

	std::shared_ptr<Object2D> icon_;
	std::shared_ptr<Animator2D> animation_;
	
	std::function<int()> get_current_hp_;

	VECTOR effect_pos_;
	float dark_percent_;
};
