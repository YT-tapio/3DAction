#pragma once

class Object2D;

// ˆê”ÔŒã‚ë‚É•`‰æ‚³‚ê‚éui
class PlayerLastBackGroundUI
{
public:

	PlayerLastBackGroundUI();

	~PlayerLastBackGroundUI();

	void Draw();

private:

	void LoadFile();

private:

	std::shared_ptr<Object2D> last_background_;
	int alpha_value_;
};