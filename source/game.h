#pragma once
#include"scene_base.h"
#include<vector>

class Camera;
class ObjectBase;
class ShadowMap;
class PlayerUIGroup;
class PlayerSkillUIGroup;
class GameStartTimer;

class Game : public SceneBase
{
public:

	Game();

	~Game() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	const std::string GetName() const override;

private:

	std::shared_ptr<Camera> camera_;
	std::shared_ptr<ShadowMap> shadow_map_;
	std::shared_ptr<PlayerUIGroup> player_ui_group_;
	std::shared_ptr<PlayerSkillUIGroup> player_skill_ui_group_;

	std::shared_ptr<GameStartTimer> game_start_timer_;

	std::vector<std::shared_ptr<ObjectBase>> objects_;
	// ‰e‚ª‚Â‚©‚È‚¢‚à‚Ì
	std::vector<std::shared_ptr<ObjectBase>> no_shadow_objects_;

	bool game_start_;
	bool is_finished_fade_;
};