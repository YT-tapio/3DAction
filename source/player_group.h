#pragma once

class Player;

class PlayerGroup
{
public:

	static PlayerGroup& GetInstance()
	{
		static PlayerGroup instance;
		return instance;
	}

	PlayerGroup(const PlayerGroup&) = delete;
	PlayerGroup& operator = (const PlayerGroup&) = delete;

	void Awake(VECTOR* camera_dir);

	void Init();

	void Update();

	void LateUpdate();

	void Draw();

	void Debug();

	VECTOR* GetCurrentPlayerHeadPos();

private:

	PlayerGroup();

	void CheckCurrentPlayerHeadPos();

	std::vector<std::shared_ptr<Player>> players_;

	VECTOR current_player_head_pos_;
	VECTOR* camera_dir_;
};