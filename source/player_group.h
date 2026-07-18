#pragma once

class Player;
class IPlayerUIGroup;

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

	void Awake(VECTOR* camera_dir, std::shared_ptr<IPlayerUIGroup> player_ui_group);

	void Init();

	void Update();

	void End();

	void LateUpdate();

	void Draw();

	void Debug();

	VECTOR* GetCurrentPlayerHeadPos();

	/// <summary>
	/// ˆø”‚Éˆê”Ô‹ß‚¢player‚ÌˆÊ’u‚ğ•Ô‚·
	/// </summary>
	/// <param name="pos">object‚Ìpos</param>
	/// <returns></returns>
	VECTOR MostNearPlayerPos(const VECTOR& pos);

private:

	PlayerGroup();

	void CheckCurrentPlayerHeadPos();

	std::vector<std::shared_ptr<Player>> players_;

	VECTOR current_player_head_pos_;
	VECTOR* camera_dir_;
};