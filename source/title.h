#pragma once
#include"scene_base.h"

class SkyDome;
class ButtonUI;

class Title : public SceneBase
{
public:

	Title();

	~Title() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	const std::string GetName() const override;

private:

	std::shared_ptr<ButtonUI> start_button_;

	int title_logo_handle_;
	int player_handle_;
	int enemy_handle_;
	int stage_handle_;
	int sky_dome_handle_;

	bool is_push_;
};
