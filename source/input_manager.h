#pragma once

class InputBase;
class IInputChange;

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

	void StopAllInput();

	void StartAllInput();

	const std::shared_ptr<const InputBase> GetPlayer1Input() const;

	const std::shared_ptr<const InputBase> GetPlayer2Input() const;

	const std::shared_ptr<const InputBase> GetPlayer3Input() const;
	
	const std::shared_ptr<const InputBase> GetPlayer4Input() const;

	const std::shared_ptr<const InputBase> GetMainPlayerInput() const;

	const bool IsPushMainInput(const std::string& name) const;

private:

	InputManager();

	void Awake();

	void ChangeInput();



private:

	static constexpr int kPlayer1Id = 1;
	static constexpr int kPlayer2Id = 2;
	static constexpr int kPlayer3Id = 3;
	static constexpr int kPlayer4Id = 4;

	std::unordered_map<int,std::weak_ptr<IInputChange>> input_changers_;
	std::unordered_map<int, std::shared_ptr<InputBase>> input_id_mp_;

	int changers_num_;
};
