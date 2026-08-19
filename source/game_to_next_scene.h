#pragma once
#include"player_observer_interface.h"
#include"enemy_observer_interface.h"

class VariableTimer;

class GameToNextScene : public IPlayerObserver, public IEnemyObserver
{
public:

	GameToNextScene();

	~GameToNextScene();

	void Init();

	bool Update();

	void OnPlayerDeath() override;

	void OnEnemyDeath() override;

private:

	std::shared_ptr<VariableTimer> timer_;

	std::string next_scene_;

	bool is_active_;

};