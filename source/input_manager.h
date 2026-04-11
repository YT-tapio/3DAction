#pragma once

class InputBase;

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

	void Init();

	void Update();

	const std::shared_ptr<const InputBase> GetPlayerInput() const;

	const std::shared_ptr<const InputBase> GetAIInput() const;

	const std::shared_ptr<const InputBase> GetAIInput2() const;
	
	const std::shared_ptr<const InputBase> GetAIInput3() const;

private:

	// ƒ}ƒbƒv‚ÅŠÇ—‚µ‚½•û‚ª‚æ‚³‚»‚¤
	// player‚Ì‘€ì‚Æai‚Ì‘€ì‚Å•ª‚¯‚æ‚¤‚©‚È
	std::shared_ptr<InputBase> player_input_;
	std::shared_ptr<InputBase> ai_input_;
	std::shared_ptr<InputBase> ai_input_2;
	std::shared_ptr<InputBase> ai_input_3;

	InputManager();

	void Awake();

};
