#pragma once
#include"config_name.h"

class InputBase;
class IInputChange;
class PlayerGroup;

class InputManager
{
public:

	static InputManager& GetInstance()
	{
		static InputManager instance;
		return instance;
	}

	InputManager(const InputManager&) = delete;
	InputManager& operator = (const InputManager&) = delete;

	void AddInput(std::weak_ptr<IInputChange> input);

	void Init();

	void Update();

	void SetPlayerGroup(std::weak_ptr<PlayerGroup> player_group);

	void StopAllInput();

	void StartAllInput();

	void DeleteResource();

	const std::shared_ptr<InputBase> GetPlayer1Input() const;

	const std::shared_ptr<InputBase> GetPlayer2Input() const;

	const std::shared_ptr<InputBase> GetPlayer3Input() const;
	
	const std::shared_ptr<InputBase> GetPlayer4Input() const;

	const std::shared_ptr<const InputBase> GetMainPlayerInput() const;

	const bool IsPushMainInput(ConfigName name) const;

private:

	InputManager();

	void Awake();

	void ChangeInput();

	/// <summary>
	/// ‡”Ô‚ğ‚½‚¾‚·
	/// </summary>
	void ResetInput();

private:

	static constexpr int kPlayer1Id = 1;
	static constexpr int kPlayer2Id = 2;
	static constexpr int kPlayer3Id = 3;
	static constexpr int kPlayer4Id = 4;

	std::unordered_map<int,std::weak_ptr<IInputChange>> input_changers_;	// input‚Ì•ÏX‚ğ‚³‚ê‚é”
	std::unordered_map<int, std::shared_ptr<InputBase>> input_id_mp_;		// input‚Ì”

	int changers_num_;
};
