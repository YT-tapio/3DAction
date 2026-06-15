#pragma once

class Animator2D;

class PlayerIconUI
{
public:

	PlayerIconUI(const std::string& name);

	~PlayerIconUI();

	void Update();

	const void Draw() const;

private:

	void LoadFile(const std::string& name);

private:

	std::shared_ptr<Object2D> icon_;
	std::shared_ptr<Animator2D> animation_;
	
	VECTOR effect_pos_;

};
