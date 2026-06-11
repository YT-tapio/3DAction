#pragma once

class PlayerIconUI
{
public:

	PlayerIconUI(const std::string& name);

	~PlayerIconUI();

	const void Draw() const;

private:

	void LoadFile(const std::string& name);

private:
	
	std::shared_ptr<Object2D> icon_;

};
